#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "ui_logindialog.h"
#include<QMap>
#include<UserInfo.h>

class Register;//前置声明

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_registerButton_clicked();//处理注册按钮点击事件
    void on_loginButton_clicked();//处理登录按钮点击事件
    void on_register_cancel();//注册取消
    void on_register_success();//注册成功

private:
    Ui::LoginDialog *ui;
    QMap<QString,User> userDatabase;
    void initUserDatabase();
};

#endif // LOGINDIALOG_H
