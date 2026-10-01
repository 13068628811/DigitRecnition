#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QList>
#include <QStringList>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

// ==========================================
// 后台搬运工类
// ==========================================
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void doWork(QList<QVector<float>> dataList);

signals:
    // 核心修改：传回一个字符串列表，每个元素对应一个数字的 Python 原始输出
    void resultReady(QStringList rawResults);
};

// ==========================================
// 主窗口类
// ==========================================
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void requestWorkerToRecognize(QList<QVector<float>> dataList);

private:
    Ui::Widget *ui;
    QImage img;

    QVector<float> pixmap2Tensor(QPixmap pix);
    std::vector<cv::Mat> splitDigits(QPixmap pix);
    void paintEvent(QPaintEvent* ev) override;

    QThread *workerThread;
    Worker *worker;
};

#endif // WIDGET_H