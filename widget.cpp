#include "widget.h"
#include "./ui_widget.h"
#include <QProcess>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QRegularExpression>
#include <QMetaType>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QProcessEnvironment>

void Worker::doWork(QList<QVector<float>> dataList)
{
    const QDir appDir(QCoreApplication::applicationDirPath());
    QSettings settings(appDir.filePath("runtime.ini"), QSettings::IniFormat);
    QString pythonPath = qEnvironmentVariable("DIGIT_PYTHON");
    if (pythonPath.isEmpty())
        pythonPath = settings.value("recognition/python", "D:/pytorch_env/Scripts/python.exe").toString();
    if ((pythonPath.contains('/') || pythonPath.contains('\\')) && QDir::isRelativePath(pythonPath))
        pythonPath = appDir.absoluteFilePath(pythonPath);
    QStringList results;

    for(const auto& data : dataList) {
        QProcess p;
        QStringList args;
        args << appDir.filePath("predict.py");

        QString dataStr;
        for(auto f : data) {
            dataStr += QString::number(f) + ",";
        }
        if(!dataStr.isEmpty()) dataStr.chop(1);
        args << dataStr;

        p.setWorkingDirectory(appDir.absolutePath());
        QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
        environment.insert("PYTHONUTF8", "1");
        environment.insert("PYTHONIOENCODING", "utf-8");
        p.setProcessEnvironment(environment);

        p.start(pythonPath, args);
        p.waitForFinished(-1);

        QString e = QString::fromUtf8(p.readAllStandardOutput()).trimmed();
        results.append(e);
    }

    emit resultReady(results);
}

// ==========================================
// 2. 主界面初始化与线程绑定
// ==========================================
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 注册跨线程类型
    qRegisterMetaType<QList<QVector<float>>>("QList<QVector<float>>");

    ui->writelabel->setFixedSize(304, 304);
    ui->writelabel->move(250, 30);
    ui->writelabel->setStyleSheet("border: 2px solid black;");
    ui->writelabel->show();

    connect(ui->pushbutton_clean, &QPushButton::clicked, [=](){
        ui->writelabel->clean();
    });
    connect(ui->pushButton_clear, &QPushButton::clicked, [=](){
        ui->writelabel->clear();
    });
    connect(ui->widget_2, &penwide::passwide, ui->writelabel, &WriteLabel::receivewide);
    connect(ui->widget_3, &ChoseColor::passpencolor, ui->writelabel, &WriteLabel::receivecolor);

    QTimer::singleShot(0, this, [=](){
        ui->writelabel->receivewide(60);
    });

    ui->resultLabel->setStyleSheet(
        "background-color: white;"
        "color: black;"
        "border: 1px solid #dcdcdc;"
        "border-radius: 8px;"
        );

    workerThread = new QThread(this);
    worker = new Worker();
    worker->moveToThread(workerThread);

    connect(this, &Widget::requestWorkerToRecognize, worker, &Worker::doWork);


    connect(worker, &Worker::resultReady, this, [=](QStringList rawResults){
        if(rawResults.isEmpty()) return;

        QString finalHtml;
        if (rawResults.size() == 1) {
            QString e = rawResults.first();
            e.remove("\n");
            e.remove("\r");
            e.remove("<br>");
            e.replace("1st:", "|1st:");
            e.replace("2nd:", "|2nd:");
            e.replace("3rd:", "|3rd:");

            QStringList parts = e.split("|", Qt::SkipEmptyParts);
            QString mainDigit = parts.size() > 0 ? parts[0].trimmed() : "";
            QString p1 = parts.size() > 1 ? parts[1].trimmed() : "";
            QString p2 = parts.size() > 2 ? parts[2].trimmed() : "";
            QString p3 = parts.size() > 3 ? parts[3].trimmed() : "";

            finalHtml = QString(
                            "<table width='100%' cellpadding='0' cellspacing='0'>"
                            "<tr><td align='center'><span style='font-size: 60pt; font-weight: bold; color: black;'>%1</span></td></tr>"
                            "<tr><td align='center'>"
                            "<table cellpadding='0' cellspacing='0'>"
                            "<tr><td align='left'><span style='font-size: 14pt; color: black;'>%2</span></td></tr>"
                            "<tr><td align='left'><span style='font-size: 14pt; color: black;'>%3</span></td></tr>"
                            "<tr><td align='left'><span style='font-size: 14pt; color: black;'>%4</span></td></tr>"
                            "</table>"
                            "</td></tr>"
                            "</table>"
                            ).arg(mainDigit, p1, p2, p3);

        }
        else {
            QString finalNumber = "";
            QRegularExpression re("\\[(\\d)\\]");

            for(const QString& raw : rawResults) {
                QRegularExpressionMatch match = re.match(raw);
                if (match.hasMatch()) {
                    finalNumber += match.captured(1);
                }
            }

            finalHtml = QString(
                            "<table width='100%' cellpadding='0' cellspacing='0'>"
                            "<tr><td align='center'><span style='font-size: 60pt; font-weight: bold; color: black;'>%1</span></td></tr>"
                            "<tr><td align='center'><span style='font-size: 14pt; color: gray;'>多数字连写模式</span></td></tr>"
                            "</table>"
                            ).arg(finalNumber);
        }

        ui->resultLabel->setText(finalHtml);
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_1->setText("预测");
    });

    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread->start();

    connect(ui->pushButton_1, &QPushButton::clicked, this, [=](){
        std::vector<cv::Mat> digitImages = splitDigits(ui->writelabel->pix);
        if(digitImages.empty()) return;

        ui->pushButton_1->setEnabled(false);
        ui->pushButton_1->setText("识别中...");

        QList<QVector<float>> taskList;
        for(size_t i = 0; i < digitImages.size(); i++) {
            cv::Mat mat = digitImages[i];
            QImage qimg(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
            QPixmap pix = QPixmap::fromImage(qimg);
            taskList.append(pixmap2Tensor(pix));
        }

        emit requestWorkerToRecognize(taskList);
    });
}

Widget::~Widget()
{
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

void Widget::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.drawImage(0,0,img);
}

// ==========================================
// 3. OpenCV 切割算法
// ==========================================
std::vector<cv::Mat> Widget::splitDigits(QPixmap pix)
{
    QImage img = pix.toImage().convertToFormat(QImage::Format_Grayscale8);
    cv::Mat mat(img.height(), img.width(), CV_8UC1, (void*)img.constBits(), img.bytesPerLine());

    cv::Mat thresh;
    cv::threshold(mat, thresh, 200, 255, cv::THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<cv::Rect> boxes;
    for(size_t i = 0; i < contours.size(); i++) {
        cv::Rect box = cv::boundingRect(contours[i]);
        if(box.area() > 50) {
            boxes.push_back(box);
        }
    }

    std::sort(boxes.begin(), boxes.end(), [](const cv::Rect& a, const cv::Rect& b){
        return a.x < b.x;
    });

    std::vector<cv::Mat> digits;
    for(auto& box : boxes) {
        int pad = 8;
        int x = std::max(0, box.x - pad);
        int y = std::max(0, box.y - pad);
        int w = std::min(mat.cols - x, box.width + 2 * pad);
        int h = std::min(mat.rows - y, box.height + 2 * pad);

        cv::Rect paddedBox(x, y, w, h);
        cv::Mat singleDigit = mat(paddedBox).clone();
        digits.push_back(singleDigit);
    }

    return digits;
}

// ==========================================
// 4. 重心居中与 Tensor 生成
// ==========================================
QVector<float> Widget::pixmap2Tensor(QPixmap pix)
{
    QImage original = pix.toImage().convertToFormat(QImage::Format_Grayscale8);
    int top = original.height(), bottom = 0;
    int left = original.width(), right = 0;
    bool hasInk = false;

    for(int y=0; y<original.height(); y++) {
        for(int x=0; x<original.width(); x++) {
            if(original.pixelColor(x,y).red() < 240) {
                if(x < left) left = x;
                if(x > right) right = x;
                if(y < top) top = y;
                if(y > bottom) bottom = y;
                hasInk = true;
            }
        }
    }

    QImage scaledImage;
    if (hasInk) {
        QRect bounding(left, top, right - left + 1, bottom - top + 1);
        QImage cropped = original.copy(bounding);
        scaledImage = cropped.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        scaledImage = original.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    double sumX = 0, sumY = 0, totalMass = 0;
    for (int y = 0; y < scaledImage.height(); y++) {
        for (int x = 0; x < scaledImage.width(); x++) {
            double mass = 255.0 - scaledImage.pixelColor(x, y).red();
            if (mass > 0) {
                sumX += x * mass;
                sumY += y * mass;
                totalMass += mass;
            }
        }
    }

    int cx = scaledImage.width() / 2;
    int cy = scaledImage.height() / 2;
    if (totalMass > 0) {
        cx = (int)(sumX / totalMass + 0.5);
        cy = (int)(sumY / totalMass + 0.5);
    }

    int dx = 14 - cx;
    int dy = 14 - cy;

    if (dx < 0) dx = 0;
    if (dy < 0) dy = 0;
    if (dx + scaledImage.width() > 28) dx = 28 - scaledImage.width();
    if (dy + scaledImage.height() > 28) dy = 28 - scaledImage.height();

    img = QImage(28, 28, QImage::Format_Grayscale8);
    img.fill(Qt::white);
    QPainter painter(&img);
    painter.drawImage(dx, dy, scaledImage);
    painter.end();

    QVector<float> res;
    float mean = 0.1307f;
    float std_dev = 0.3081f;

    for(int y=0; y<28; y++) {
        for(int x=0; x<28; x++) {
            uchar gray = img.pixelColor(x,y).red();
            float inverted = 255.0f - gray;

            float val = inverted / 255.0f;
            val = (val - mean) / std_dev;
            res.append(val);
        }
    }
    return res;
}