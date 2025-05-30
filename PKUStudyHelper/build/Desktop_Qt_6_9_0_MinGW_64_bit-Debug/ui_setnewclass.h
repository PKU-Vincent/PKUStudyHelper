/********************************************************************************
** Form generated from reading UI file 'setnewclass.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETNEWCLASS_H
#define UI_SETNEWCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetNewClass
{
public:
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *tinfo;
    QHBoxLayout *horizontalLayout;
    QLineEdit *teachingbuilding;
    QLineEdit *classroom;
    QLineEdit *credit;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *day;
    QLineEdit *time;
    QLineEdit *week;
    QLabel *label_8;
    QLabel *label_2;
    QLabel *label_9;
    QLineEdit *atinfo;
    QLabel *label_4;
    QLabel *label_10;
    QLineEdit *teacher;
    QLabel *label_3;
    QLabel *label_6;
    QTextEdit *tip;
    QLabel *label_7;
    QLabel *label_5;
    QLineEdit *classname;
    QLineEdit *term;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *confirm;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;

    void setupUi(QWidget *SetNewClass)
    {
        if (SetNewClass->objectName().isEmpty())
            SetNewClass->setObjectName("SetNewClass");
        SetNewClass->resize(875, 594);
        label = new QLabel(SetNewClass);
        label->setObjectName("label");
        label->setGeometry(QRect(340, 10, 161, 41));
        label->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Microsoft YaHei UI\";"));
        gridLayoutWidget = new QWidget(SetNewClass);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 50, 831, 431));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tinfo = new QLineEdit(gridLayoutWidget);
        tinfo->setObjectName("tinfo");

        gridLayout->addWidget(tinfo, 6, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        teachingbuilding = new QLineEdit(gridLayoutWidget);
        teachingbuilding->setObjectName("teachingbuilding");

        horizontalLayout->addWidget(teachingbuilding);

        classroom = new QLineEdit(gridLayoutWidget);
        classroom->setObjectName("classroom");

        horizontalLayout->addWidget(classroom);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 1);

        credit = new QLineEdit(gridLayoutWidget);
        credit->setObjectName("credit");

        gridLayout->addWidget(credit, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        day = new QLineEdit(gridLayoutWidget);
        day->setObjectName("day");

        horizontalLayout_2->addWidget(day);

        time = new QLineEdit(gridLayoutWidget);
        time->setObjectName("time");

        horizontalLayout_2->addWidget(time);

        week = new QLineEdit(gridLayoutWidget);
        week->setObjectName("week");

        horizontalLayout_2->addWidget(week);


        gridLayout->addLayout(horizontalLayout_2, 5, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");

        gridLayout->addWidget(label_9, 7, 0, 1, 1);

        atinfo = new QLineEdit(gridLayoutWidget);
        atinfo->setObjectName("atinfo");

        gridLayout->addWidget(atinfo, 7, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");

        gridLayout->addWidget(label_10, 8, 0, 1, 1);

        teacher = new QLineEdit(gridLayoutWidget);
        teacher->setObjectName("teacher");

        gridLayout->addWidget(teacher, 3, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        tip = new QTextEdit(gridLayoutWidget);
        tip->setObjectName("tip");

        gridLayout->addWidget(tip, 8, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 4, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        classname = new QLineEdit(gridLayoutWidget);
        classname->setObjectName("classname");

        gridLayout->addWidget(classname, 1, 1, 1, 1);

        term = new QLineEdit(gridLayoutWidget);
        term->setObjectName("term");

        gridLayout->addWidget(term, 1, 0, 1, 1);

        horizontalLayoutWidget = new QWidget(SetNewClass);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(230, 510, 401, 51));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        confirm = new QPushButton(horizontalLayoutWidget);
        confirm->setObjectName("confirm");

        horizontalLayout_3->addWidget(confirm);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        cancel = new QPushButton(horizontalLayoutWidget);
        cancel->setObjectName("cancel");

        horizontalLayout_3->addWidget(cancel);


        retranslateUi(SetNewClass);

        QMetaObject::connectSlotsByName(SetNewClass);
    } // setupUi

    void retranslateUi(QWidget *SetNewClass)
    {
        SetNewClass->setWindowTitle(QCoreApplication::translate("SetNewClass", "Form", nullptr));
        label->setText(QCoreApplication::translate("SetNewClass", "\346\267\273\345\212\240\346\226\260\347\232\204\350\257\276\347\250\213", nullptr));
        label_8->setText(QCoreApplication::translate("SetNewClass", "                                    \346\225\231\345\270\210\350\201\224\347\273\234\344\277\241\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("SetNewClass", "\345\255\246\346\234\237", nullptr));
        label_9->setText(QCoreApplication::translate("SetNewClass", "                                    \345\212\251\346\225\231\350\201\224\347\273\234\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("SetNewClass", "\345\255\246\345\210\206", nullptr));
        label_10->setText(QCoreApplication::translate("SetNewClass", "                                                  \345\244\207\346\263\250", nullptr));
        label_3->setText(QCoreApplication::translate("SetNewClass", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        label_6->setText(QCoreApplication::translate("SetNewClass", "\344\270\212\350\257\276\345\234\260\347\202\271", nullptr));
        label_7->setText(QCoreApplication::translate("SetNewClass", "\344\270\212\350\257\276\346\227\266\351\227\264", nullptr));
        label_5->setText(QCoreApplication::translate("SetNewClass", "\346\216\210\350\257\276\346\225\231\345\270\210", nullptr));
        confirm->setText(QCoreApplication::translate("SetNewClass", "\344\277\235\345\255\230", nullptr));
        cancel->setText(QCoreApplication::translate("SetNewClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetNewClass: public Ui_SetNewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETNEWCLASS_H
