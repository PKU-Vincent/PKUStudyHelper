/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *welcome;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *account;
    QLabel *code;
    QLineEdit *aedit;
    QLineEdit *cedit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginbutton;
    QPushButton *registerbutton;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(611, 382);
        LoginDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);"));
        welcome = new QLabel(LoginDialog);
        welcome->setObjectName("welcome");
        welcome->setGeometry(QRect(100, 40, 381, 41));
        welcome->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Microsoft YaHei UI\";\n"
"color: rgb(255, 12, 57);"));
        gridLayoutWidget = new QWidget(LoginDialog);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(100, 120, 371, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        account = new QLabel(gridLayoutWidget);
        account->setObjectName("account");

        gridLayout->addWidget(account, 0, 0, 1, 1);

        code = new QLabel(gridLayoutWidget);
        code->setObjectName("code");

        gridLayout->addWidget(code, 2, 0, 1, 1);

        aedit = new QLineEdit(gridLayoutWidget);
        aedit->setObjectName("aedit");

        gridLayout->addWidget(aedit, 0, 1, 1, 1);

        cedit = new QLineEdit(gridLayoutWidget);
        cedit->setObjectName("cedit");

        gridLayout->addWidget(cedit, 2, 1, 1, 1);

        horizontalLayoutWidget = new QWidget(LoginDialog);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(190, 260, 202, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(14);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        loginbutton = new QPushButton(horizontalLayoutWidget);
        loginbutton->setObjectName("loginbutton");

        horizontalLayout->addWidget(loginbutton);

        registerbutton = new QPushButton(horizontalLayoutWidget);
        registerbutton->setObjectName("registerbutton");

        horizontalLayout->addWidget(registerbutton);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        welcome->setText(QCoreApplication::translate("LoginDialog", "Welcome  to  PKUStudyHelper  ! ", nullptr));
        account->setText(QCoreApplication::translate("LoginDialog", "     \350\264\246\345\217\267\357\274\232", nullptr));
        code->setText(QCoreApplication::translate("LoginDialog", "     \345\257\206\347\240\201\357\274\232", nullptr));
        loginbutton->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        registerbutton->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
