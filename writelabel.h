#ifndef WRITELABEL_H
#define WRITELABEL_H

#include <QLabel>
#include<QMouseEvent>
#include<QPixmap>
#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QPoint>
#include<QColor>
#include<QPen>
class WriteLabel : public QLabel
{
    Q_OBJECT
public:
    explicit WriteLabel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void clean();
    void clear();
    void receivewide(int a);
    void receivecolor(QColor a);
    QPixmap pix;
    QPixmap pix2;
    bool isdrawing;
    bool iseraser;
    QColor color;
    int penwidth=60;
    QPoint last;
signals:
};

#endif // WRITELABEL_H
