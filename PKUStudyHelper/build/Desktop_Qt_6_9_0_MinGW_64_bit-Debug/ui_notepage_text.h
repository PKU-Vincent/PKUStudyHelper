/********************************************************************************
** Form generated from reading UI file 'notepage_text.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAGE_TEXT_H
#define UI_NOTEPAGE_TEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotePage
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_2;
    QLineEdit *time;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *NotePage)
    {
        if (NotePage->objectName().isEmpty())
            NotePage->setObjectName("NotePage");
        NotePage->resize(1057, 660);
        horizontalLayoutWidget = new QWidget(NotePage);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(40, 10, 961, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(horizontalLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout->addWidget(lineEdit_2);

        time = new QLineEdit(horizontalLayoutWidget);
        time->setObjectName("time");

        horizontalLayout->addWidget(time);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        textEdit = new QTextEdit(NotePage);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(40, 90, 931, 501));
        pushButton = new QPushButton(NotePage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(430, 610, 161, 28));

        retranslateUi(NotePage);

        QMetaObject::connectSlotsByName(NotePage);
    } // setupUi

    void retranslateUi(QWidget *NotePage)
    {
        NotePage->setWindowTitle(QCoreApplication::translate("NotePage", "Form", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("NotePage", "5.29", nullptr));
        time->setText(QCoreApplication::translate("NotePage", "\347\275\221\347\273\234\347\210\254\350\231\253", nullptr));
        pushButton->setText(QCoreApplication::translate("NotePage", "\344\270\200\351\224\256\347\224\237\346\210\220\346\200\235\347\273\264\345\257\274\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotePage: public Ui_NotePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAGE_TEXT_H
