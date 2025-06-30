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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *welcome;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label1;
    QLabel *label2;
    QLineEdit *account;
    QLineEdit *password;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *registerbutton;
    QLabel *label;
    QLabel *label_image;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(780, 520);
        LoginDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);"));
        welcome = new QLabel(LoginDialog);
        welcome->setObjectName("welcome");
        welcome->setGeometry(QRect(20, 40, 381, 41));
        welcome->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Microsoft YaHei UI\";\n"
"color: rgb(255, 12, 57);"));
        gridLayoutWidget = new QWidget(LoginDialog);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 110, 371, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label1 = new QLabel(gridLayoutWidget);
        label1->setObjectName("label1");
        label1->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(label1, 0, 0, 1, 1);

        label2 = new QLabel(gridLayoutWidget);
        label2->setObjectName("label2");
        label2->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(label2, 2, 0, 1, 1);

        account = new QLineEdit(gridLayoutWidget);
        account->setObjectName("account");

        gridLayout->addWidget(account, 0, 1, 1, 1);

        password = new QLineEdit(gridLayoutWidget);
        password->setObjectName("password");
        password->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(password, 2, 1, 1, 1);

        horizontalLayoutWidget = new QWidget(LoginDialog);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(50, 260, 285, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(14);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        loginButton = new QPushButton(horizontalLayoutWidget);
        loginButton->setObjectName("loginButton");
        loginButton->setStyleSheet(QString::fromUtf8("\n"
"            background-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgba(255, 0, 150, 204), stop:1 rgba(0, 204, 255, 204));\n"
"            \n"
"font: 700 9pt \"Microsoft YaHei UI\";\n"
"            color: white;\n"
"            border: none;\n"
"            border-radius: 15px;\n"
"            padding: 10px 20px;\n"
"            letter-spacing: 1.5px;\n"
"      "));

        horizontalLayout->addWidget(loginButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        registerbutton = new QPushButton(horizontalLayoutWidget);
        registerbutton->setObjectName("registerbutton");
        registerbutton->setStyleSheet(QString::fromUtf8("\n"
"            background-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgba(255, 0, 150, 204), stop:1 rgba(0, 204, 255, 204));\n"
"            \n"
"font: 700 9pt \"Microsoft YaHei UI\";\n"
"            color: white;\n"
"            border: none;\n"
"            border-radius: 15px;\n"
"            padding: 10px 20px;\n"
"            letter-spacing: 1.5px;\n"
"      "));

        horizontalLayout->addWidget(registerbutton);

        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 370, 241, 51));
        label_image = new QLabel(LoginDialog);
        label_image->setObjectName("label_image");
        label_image->setGeometry(QRect(390, -20, 391, 551));
        label_image->setStyleSheet(QString::fromUtf8("image:url(:/new/prefix1/boyata.image);\n"
""));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        welcome->setText(QCoreApplication::translate("LoginDialog", "Welcome  to  PKUStudyHelper  ! ", nullptr));
        label1->setText(QCoreApplication::translate("LoginDialog", "     \350\264\246\345\217\267\357\274\232", nullptr));
        label2->setText(QCoreApplication::translate("LoginDialog", "     \345\257\206\347\240\201\357\274\232", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        registerbutton->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
        label->setText(QString());
        label_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
