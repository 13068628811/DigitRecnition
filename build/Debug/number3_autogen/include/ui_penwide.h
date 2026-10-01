/********************************************************************************
** Form generated from reading UI file 'penwide.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PENWIDE_H
#define UI_PENWIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_penwide
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QScrollBar *ScrollBar_penwide;

    void setupUi(QWidget *penwide)
    {
        if (penwide->objectName().isEmpty())
            penwide->setObjectName("penwide");
        penwide->resize(400, 300);
        verticalLayout = new QVBoxLayout(penwide);
        verticalLayout->setObjectName("verticalLayout");
        widget_2 = new QWidget(penwide);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(penwide);
        widget->setObjectName("widget");
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        ScrollBar_penwide = new QScrollBar(widget);
        ScrollBar_penwide->setObjectName("ScrollBar_penwide");
        ScrollBar_penwide->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(ScrollBar_penwide);


        verticalLayout->addWidget(widget);


        retranslateUi(penwide);

        QMetaObject::connectSlotsByName(penwide);
    } // setupUi

    void retranslateUi(QWidget *penwide)
    {
        penwide->setWindowTitle(QCoreApplication::translate("penwide", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("penwide", "\347\224\273\347\254\224\347\262\227\347\273\206\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("penwide", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class penwide: public Ui_penwide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PENWIDE_H
