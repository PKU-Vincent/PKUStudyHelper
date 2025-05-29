/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *aboveword;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1202, 722);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        aboveword = new QLabel(centralwidget);
        aboveword->setObjectName("aboveword");
        aboveword->setGeometry(QRect(0, 0, 1191, 31));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(0, 30, 1191, 651));
        splitter->setOrientation(Qt::Orientation::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        treeWidget->headerItem()->setText(0, QString());
        new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(treeWidget);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";\n"
""));
        splitter->addWidget(treeWidget);
        stackedWidget = new QStackedWidget(splitter);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        splitter->addWidget(stackedWidget);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1202, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        aboveword->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->topLevelItem(0);
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\344\270\273\351\241\265", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\350\257\276\347\250\213", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "\351\253\230\347\255\211\346\225\260\345\255\246\357\274\210A\357\274\211\357\274\210\344\272\214\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "\347\272\277\346\200\247\344\273\243\346\225\260\357\274\210A\357\274\211\357\274\210\344\272\214\357\274\211", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "\344\272\272\345\267\245\346\231\272\350\203\275\345\274\225\350\256\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "\344\272\272\345\267\245\346\231\272\350\203\275\345\237\272\347\241\200", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("MainWindow", "\345\234\260\351\234\207\346\246\202\350\256\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(5);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("MainWindow", "\344\270\255\345\233\275\350\277\221\344\273\243\345\217\262\347\272\262\350\246\201", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\344\273\273\345\212\241", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
