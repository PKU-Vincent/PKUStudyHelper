/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Homepage
{
public:
    QTextBrowser *textBrowser;
    QTableWidget *tableWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *viewcompletetable;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QTableWidget *tableWidget_2;
    QLabel *label_4;
    QTableWidget *tableWidget_3;

    void setupUi(QWidget *Homepage)
    {
        if (Homepage->objectName().isEmpty())
            Homepage->setObjectName("Homepage");
        Homepage->resize(1056, 678);
        textBrowser = new QTextBrowser(Homepage);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(20, 20, 771, 71));
        tableWidget = new QTableWidget(Homepage);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 130, 381, 541));
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(15);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        horizontalLayoutWidget = new QWidget(Homepage);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 100, 331, 30));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));

        horizontalLayout->addWidget(label);

        viewcompletetable = new QPushButton(horizontalLayoutWidget);
        viewcompletetable->setObjectName("viewcompletetable");

        horizontalLayout->addWidget(viewcompletetable);

        horizontalLayoutWidget_2 = new QWidget(Homepage);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(420, 100, 361, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(Homepage);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(580, 140, 111, 21));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));
        tableWidget_2 = new QTableWidget(Homepage);
        if (tableWidget_2->columnCount() < 4)
            tableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(390, 170, 501, 181));
        tableWidget_2->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget_2->verticalHeader()->setMinimumSectionSize(20);
        tableWidget_2->verticalHeader()->setDefaultSectionSize(29);
        tableWidget_2->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget_2->verticalHeader()->setStretchLastSection(true);
        label_4 = new QLabel(Homepage);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(600, 360, 101, 21));
        label_4->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));
        tableWidget_3 = new QTableWidget(Homepage);
        if (tableWidget_3->columnCount() < 2)
            tableWidget_3->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(390, 400, 521, 261));

        retranslateUi(Homepage);

        QMetaObject::connectSlotsByName(Homepage);
    } // setupUi

    void retranslateUi(QWidget *Homepage)
    {
        Homepage->setWindowTitle(QCoreApplication::translate("Homepage", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Homepage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\227\251\344\270\212\345\245\275\357\274\214\345\260\217\345\214\227\357\274\201\345\217\210\346\230\257\347\276\216\345\245\275\347\232\204\344\270\200\345\244\251\357\274\201</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\216\260\345\234\250\346\230\2572025\345\271\2645\346\234\21028\346\227\24523:15"
                        "\357\274\214\347\245\235\344\275\240\350\203\275\347\235\241\344\270\252\345\245\275\350\247\211\357\274\201</p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Homepage", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Homepage", "\350\257\276\347\250\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Homepage", "\345\234\260\347\202\271", nullptr));
        label->setText(QCoreApplication::translate("Homepage", "\346\235\245\347\234\213\347\234\213\344\273\212\345\244\251\347\232\204\350\257\276\347\250\213\350\241\250\345\220\247\357\274\232", nullptr));
        viewcompletetable->setText(QCoreApplication::translate("Homepage", "\347\202\271\346\210\221\346\237\245\347\234\213\345\256\214\346\225\264\350\257\276\347\250\213\350\241\250", nullptr));
        label_2->setText(QCoreApplication::translate("Homepage", "\344\273\212\345\244\251\344\275\240\351\203\275\346\234\211\345\223\252\344\272\233\344\273\273\345\212\241\345\221\242\357\274\237", nullptr));
        label_3->setText(QCoreApplication::translate("Homepage", "\346\234\200\350\277\221\347\232\204DDL", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Homepage", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Homepage", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Homepage", "\344\273\273\345\212\241", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Homepage", "\345\256\214\346\210\220", nullptr));
        label_4->setText(QCoreApplication::translate("Homepage", "To-do List", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Homepage", "\345\256\214\346\210\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Homepage", "\344\273\273\345\212\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Homepage: public Ui_Homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
