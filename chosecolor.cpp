#include "chosecolor.h"
#include "ui_chosecolor.h"

ChoseColor::ChoseColor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoseColor)
{
    ui->setupUi(this);
    connect(ui->pushButton_choosecolor,&QPushButton::clicked,this,[=](){
        pencolor=QColorDialog::getColor(QColor(0,0,0));
        emit passpencolor(pencolor);
    });
}

ChoseColor::~ChoseColor()
{
    delete ui;
}
