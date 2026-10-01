/********************************************************************************
** Form generated from reading UI file 'chosecolor.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOSECOLOR_H
#define UI_CHOSECOLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChoseColor
{
public:
    QPushButton *pushButton_choosecolor;

    void setupUi(QWidget *ChoseColor)
    {
        if (ChoseColor->objectName().isEmpty())
            ChoseColor->setObjectName("ChoseColor");
        ChoseColor->resize(100, 50);
        ChoseColor->setMinimumSize(QSize(100, 50));
        ChoseColor->setMaximumSize(QSize(100, 50));
        ChoseColor->setStyleSheet(QString::fromUtf8(""));
        pushButton_choosecolor = new QPushButton(ChoseColor);
        pushButton_choosecolor->setObjectName("pushButton_choosecolor");
        pushButton_choosecolor->setGeometry(QRect(0, 0, 100, 50));
        pushButton_choosecolor->setMinimumSize(QSize(100, 50));
        pushButton_choosecolor->setMaximumSize(QSize(100, 50));
        pushButton_choosecolor->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        retranslateUi(ChoseColor);

        QMetaObject::connectSlotsByName(ChoseColor);
    } // setupUi

    void retranslateUi(QWidget *ChoseColor)
    {
        ChoseColor->setWindowTitle(QCoreApplication::translate("ChoseColor", "Form", nullptr));
        pushButton_choosecolor->setText(QCoreApplication::translate("ChoseColor", "\351\200\211\346\213\251\347\224\273\347\254\224\351\242\234\350\211\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChoseColor: public Ui_ChoseColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOSECOLOR_H
