#ifndef PENWIDE_H
#define PENWIDE_H

#include <QWidget>

namespace Ui {
class penwide;
}

class penwide : public QWidget
{
    Q_OBJECT

public:
    explicit penwide(QWidget *parent = nullptr);
    int wide;
    ~penwide();

private:
    Ui::penwide *ui;
signals:
    void passwide(int);
};

#endif // PENWIDE_H
