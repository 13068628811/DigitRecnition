#ifndef CHOSECOLOR_H
#define CHOSECOLOR_H

#include <QPushButton>
#include<QColorDialog>
#include<QDebug>
namespace Ui {
class ChoseColor;
}

class ChoseColor : public QWidget
{
    Q_OBJECT

public:
    explicit ChoseColor(QWidget *parent = nullptr);
    ~ChoseColor();
    QColor pencolor;

private:
    Ui::ChoseColor *ui;
signals:
    void passpencolor(QColor a);
};

#endif // CHOSECOLOR_H
