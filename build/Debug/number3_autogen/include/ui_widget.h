/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "chosecolor.h"
#include "penwide.h"
#include "writelabel.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    WriteLabel *writelabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_1;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushbutton_clean;
    penwide *widget_2;
    QPushButton *pushButton_clear;
    ChoseColor *widget_3;
    QLabel *resultLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        Widget->setMinimumSize(QSize(500, 600));
        QFont font;
        font.setPointSize(9);
        Widget->setFont(font);
        writelabel = new WriteLabel(Widget);
        writelabel->setObjectName("writelabel");
        writelabel->setGeometry(QRect(270, 10, 304, 304));
        writelabel->setMinimumSize(QSize(304, 304));
        writelabel->setMaximumSize(QSize(304, 304));
        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(250, 350, 300, 62));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_1 = new QPushButton(widget);
        pushButton_1->setObjectName("pushButton_1");
        pushButton_1->setMinimumSize(QSize(100, 50));
        pushButton_1->setMaximumSize(QSize(100, 50));
        pushButton_1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    /* \344\270\200\346\254\241\346\200\247\350\256\276\347\275\256\357\274\232\345\256\275\345\272\246 + \346\240\267\345\274\217 + \351\242\234\350\211\262 */\n"
"    border: 2px solid #666;\n"
"    border-radius: 6px;\n"
"    background-color: #f0f0f0;\n"
"    color: #333;\n"
"    padding: 5px 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e0e0e0;\n"
"    border-color: #333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d0d0d0;\n"
"    border-color: #111;\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton_1);

        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushbutton_clean = new QPushButton(widget);
        pushbutton_clean->setObjectName("pushbutton_clean");
        pushbutton_clean->setMinimumSize(QSize(100, 50));
        pushbutton_clean->setMaximumSize(QSize(100, 50));
        pushbutton_clean->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    /* \344\270\200\346\254\241\346\200\247\350\256\276\347\275\256\357\274\232\345\256\275\345\272\246 + \346\240\267\345\274\217 + \351\242\234\350\211\262 */\n"
"    border: 2px solid #666;\n"
"    border-radius: 6px;\n"
"    background-color: #f0f0f0;\n"
"    color: #333;\n"
"    padding: 5px 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e0e0e0;\n"
"    border-color: #333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d0d0d0;\n"
"    border-color: #111;\n"
"}\n"
""));

        horizontalLayout->addWidget(pushbutton_clean);

        widget_2 = new penwide(Widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(580, 9, 211, 101));
        pushButton_clear = new QPushButton(Widget);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(640, 130, 100, 50));
        pushButton_clear->setMinimumSize(QSize(100, 50));
        pushButton_clear->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    /* \344\270\200\346\254\241\346\200\247\350\256\276\347\275\256\357\274\232\345\256\275\345\272\246 + \346\240\267\345\274\217 + \351\242\234\350\211\262 */\n"
"    border: 2px solid #666;\n"
"    border-radius: 6px;\n"
"    background-color: #f0f0f0;\n"
"    color: #333;\n"
"    padding: 5px 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e0e0e0;\n"
"    border-color: #333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d0d0d0;\n"
"    border-color: #111;\n"
"}\n"
""));
        widget_3 = new ChoseColor(Widget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(640, 200, 120, 80));
        widget_3->setMinimumSize(QSize(100, 50));
        resultLabel = new QLabel(Widget);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setGeometry(QRect(10, 90, 221, 181));
        resultLabel->setFont(font);
        resultLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        resultLabel->setWordWrap(true);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        writelabel->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        pushButton_1->setText(QCoreApplication::translate("Widget", "\351\242\204\346\265\213", nullptr));
        pushbutton_clean->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Widget", "\346\251\241\347\232\256", nullptr));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
