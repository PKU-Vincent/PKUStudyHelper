/********************************************************************************
** Form generated from reading UI file 'notepage_md.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAGE_MD_H
#define UI_NOTEPAGE_MD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_notepage_md
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QTextEdit *textEdit;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *notepage_md)
    {
        if (notepage_md->objectName().isEmpty())
            notepage_md->setObjectName("notepage_md");
        notepage_md->resize(950, 594);
        horizontalLayoutWidget = new QWidget(notepage_md);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(110, 20, 781, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(horizontalLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout->addWidget(lineEdit_2);

        horizontalLayout->setStretch(1, 1);
        textEdit = new QTextEdit(notepage_md);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(50, 80, 411, 461));
        textBrowser = new QTextBrowser(notepage_md);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(490, 80, 441, 461));
        pushButton = new QPushButton(notepage_md);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 550, 131, 28));
        pushButton_2 = new QPushButton(notepage_md);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(650, 550, 141, 28));

        retranslateUi(notepage_md);

        QMetaObject::connectSlotsByName(notepage_md);
    } // setupUi

    void retranslateUi(QWidget *notepage_md)
    {
        notepage_md->setWindowTitle(QCoreApplication::translate("notepage_md", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("notepage_md", "\344\270\200\351\224\256\347\224\237\346\210\220\346\200\235\347\273\264\345\257\274\345\233\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("notepage_md", "\344\270\200\351\224\256\347\276\216\345\214\226\346\216\222\347\211\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class notepage_md: public Ui_notepage_md {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAGE_MD_H
