/********************************************************************************
** Form generated from reading UI file 'classpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSPAGE_H
#define UI_CLASSPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClassPage
{
public:
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *location;
    QPushButton *viewmore;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTableWidget *tableWidget;
    QLabel *label_3;
    QLabel *label_4;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QTableWidget *tableWidget_2;
    QTextEdit *textEdit;
    QLabel *label_5;

    void setupUi(QWidget *ClassPage)
    {
        if (ClassPage->objectName().isEmpty())
            ClassPage->setObjectName("ClassPage");
        ClassPage->resize(1057, 684);
        label = new QLabel(ClassPage);
        label->setObjectName("label");
        label->setGeometry(QRect(410, 0, 181, 41));
        label->setStyleSheet(QString::fromUtf8("font: 700 22pt \"Microsoft YaHei UI\";"));
        verticalLayoutWidget = new QWidget(ClassPage);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 60, 331, 181));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        location = new QLabel(verticalLayoutWidget);
        location->setObjectName("location");

        verticalLayout->addWidget(location);

        viewmore = new QPushButton(verticalLayoutWidget);
        viewmore->setObjectName("viewmore");

        verticalLayout->addWidget(viewmore);

        pushButton = new QPushButton(ClassPage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(390, 50, 201, 31));
        scrollArea = new QScrollArea(ClassPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(10, 290, 481, 381));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 479, 379));
        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 481, 421));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_3 = new QLabel(ClassPage);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(200, 250, 111, 31));
        label_4 = new QLabel(ClassPage);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(750, 250, 69, 19));
        scrollArea_2 = new QScrollArea(ClassPage);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(520, 290, 501, 381));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 499, 379));
        tableWidget_2 = new QTableWidget(scrollAreaWidgetContents_2);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(0, 0, 501, 381));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        textEdit = new QTextEdit(ClassPage);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(610, 90, 421, 141));
        label_5 = new QLabel(ClassPage);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(790, 51, 71, 20));

        retranslateUi(ClassPage);

        QMetaObject::connectSlotsByName(ClassPage);
    } // setupUi

    void retranslateUi(QWidget *ClassPage)
    {
        ClassPage->setWindowTitle(QCoreApplication::translate("ClassPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("ClassPage", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("ClassPage", "\344\270\212\350\257\276\346\227\266\351\227\264\357\274\232", nullptr));
        location->setText(QCoreApplication::translate("ClassPage", "\344\270\212\350\257\276\345\234\260\347\202\271\357\274\232", nullptr));
        viewmore->setText(QCoreApplication::translate("ClassPage", "\346\237\245\347\234\213\346\233\264\345\244\232\350\257\276\347\250\213\344\277\241\346\201\257", nullptr));
        pushButton->setText(QCoreApplication::translate("ClassPage", "\347\202\271\346\210\221\345\277\253\351\200\237\350\277\233\345\205\245\346\225\231\345\255\246\347\275\221", nullptr));
        label_3->setText(QCoreApplication::translate("ClassPage", "\346\210\221\347\232\204\347\254\224\350\256\260", nullptr));
        label_4->setText(QCoreApplication::translate("ClassPage", "\346\210\221\347\232\204\344\275\234\344\270\232", nullptr));
        textEdit->setHtml(QCoreApplication::translate("ClassPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\221\250\346\227\245\345\210\253\345\277\230\344\272\206\345\216\273\344\270\212\346\234\272\357\274\201</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("ClassPage", "\345\260\217\351\273\221\346\235\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClassPage: public Ui_ClassPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSPAGE_H
