#include "writelabel.h"

WriteLabel::WriteLabel(QWidget *parent)
    : QLabel{parent}
{
    pix=QPixmap(300,300);
    pix.fill(Qt::white);
    pix2=QPixmap(300,300);
    pix2.fill(Qt::white);
    color=Qt::black;
}
void WriteLabel::mousePressEvent(QMouseEvent* ev)
{
    if((ev->buttons()&Qt::LeftButton)&&!iseraser)
    {
        isdrawing=true;
        QPainter painter(&pix);
        QPainter painter1(&pix2);
        painter.setPen(QPen(Qt::black, penwidth/5, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(ev->pos());
        painter1.setPen(QPen(color, penwidth/5, Qt::SolidLine, Qt::RoundCap));
        painter1.drawPoint(ev->pos());
        this->last=ev->pos();
        update();
    }
    else
    {
        isdrawing=true;
        QPainter painter(&pix);
        QPainter painter1(&pix2);
        painter.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(ev->pos());
        painter1.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap));
        painter1.drawPoint(ev->pos());
        this->last=ev->pos();
        update();
    }
}
void WriteLabel::mouseMoveEvent(QMouseEvent*ev)
{
    if(isdrawing==true&&!iseraser)
    {
        QPainter painter(&pix);
        QPainter painter1(&pix2);
        painter.setPen(QPen(Qt::black, penwidth/5, Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(this->last,ev->pos());
        painter1.setPen(QPen(color, penwidth/5, Qt::SolidLine, Qt::RoundCap));
        painter1.drawLine(this->last,ev->pos());
        this->last=ev->pos();
        update();
    }
    else
    {
        isdrawing=true;
        QPainter painter(&pix);
        QPainter painter1(&pix2);
        painter.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(ev->pos());
        painter1.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap));
        painter1.drawPoint(ev->pos());
        this->last=ev->pos();
        update();
    }
}
void WriteLabel::mouseReleaseEvent(QMouseEvent* ev)
{
    isdrawing=false;
    iseraser=false;
}
void WriteLabel::clean()
{
    pix.fill(Qt::white);
    pix2.fill(Qt::white);
    update();
}
void WriteLabel::clear()
{
    iseraser=true;
}
void WriteLabel::receivewide(int a)
{
    this->penwidth=a;
}
void WriteLabel::receivecolor(QColor a)
{
    this->color=a;
}
void WriteLabel::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.drawPixmap(2,2,pix2);
}