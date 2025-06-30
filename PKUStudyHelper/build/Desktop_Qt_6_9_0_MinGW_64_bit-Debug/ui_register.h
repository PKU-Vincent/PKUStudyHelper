/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *yes;
    QPushButton *cancelButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLineEdit *newname;
    QLineEdit *newaccount;
    QLineEdit *newcode;
    QLineEdit *confirmpassword;
    QLabel *message;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(578, 365);
        horizontalLayoutWidget = new QWidget(Register);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(200, 240, 195, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        yes = new QPushButton(horizontalLayoutWidget);
        yes->setObjectName("yes");

        horizontalLayout->addWidget(yes);

        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        gridLayoutWidget = new QWidget(Register);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(90, 10, 391, 191));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        newname = new QLineEdit(gridLayoutWidget);
        newname->setObjectName("newname");

        gridLayout->addWidget(newname, 0, 1, 1, 1);

        newaccount = new QLineEdit(gridLayoutWidget);
        newaccount->setObjectName("newaccount");

        gridLayout->addWidget(newaccount, 2, 1, 1, 1);

        newcode = new QLineEdit(gridLayoutWidget);
        newcode->setObjectName("newcode");
        newcode->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(newcode, 3, 1, 1, 1);

        confirmpassword = new QLineEdit(gridLayoutWidget);
        confirmpassword->setObjectName("confirmpassword");
        confirmpassword->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(confirmpassword, 4, 1, 1, 1);

        message = new QLabel(Register);
        message->setObjectName("message");
        message->setGeometry(QRect(160, 330, 281, 21));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        yes->setText(QCoreApplication::translate("Register", "\347\241\256\350\256\244", nullptr));
        cancelButton->setText(QCoreApplication::translate("Register", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("Register", "\350\257\267\350\256\276\347\275\256\344\275\240\347\232\204\350\264\246\345\217\267\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Register", "\350\257\267\350\256\276\347\275\256\344\275\240\347\232\204\346\230\265\347\247\260\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Register", "\345\206\215\346\254\241\347\241\256\350\256\244\344\275\240\347\232\204\345\257\206\347\240\201\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "\350\257\267\350\256\276\347\275\256\344\275\240\347\232\204\345\257\206\347\240\201\357\274\232", nullptr));
        message->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
