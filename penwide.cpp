#include "penwide.h"
#include "ui_penwide.h"
penwide::penwide(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::penwide)
{
    ui->setupUi(this);
    wide=80;
    ui->ScrollBar_penwide->setValue(80);
    ui->label_3->setText(QString("%1").arg(wide));
    connect(ui->ScrollBar_penwide,&QScrollBar::valueChanged,ui->label_3,[=](int pos){
        ui->label_3->setText(QString("%1").arg(pos));
        wide=pos;
        emit passwide(wide);
    });
}

penwide::~penwide()
{
    delete ui;
}
