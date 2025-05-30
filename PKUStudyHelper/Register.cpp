#include "Register.h"
#include "ui_Register.h"
#include"UserInfo.h"
#include <QDebug>

extern QSqlDatabase db;

Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->yes, &QPushButton::clicked, this, &Register::on_confirmButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Register::on_cancelButton_clicked);
}

Register::~Register()
{
    delete ui;
}

void Register::on_confirmButton_clicked()
{
    QString username = ui->newname->text();
    QString account = ui->newaccount->text();
    QString password = ui->newcode->text();
    QString confirmPassword = ui->confirmpassword->text();

    if (username.isEmpty() || account.isEmpty() || password.isEmpty()) {
        ui->message->setText("用户名、账号或密码不能为空");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    if (password != confirmPassword) {
        ui->message->setText("两次输入的密码不一致");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        ui->message->setText("该用户名已存在");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    query.prepare("SELECT * FROM user WHERE account = :account");
    query.bindValue(":account", account);

    if (query.exec() && query.next()) {
        ui->message->setText("该账号已存在");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    query.prepare("INSERT INTO user (username, account, password) VALUES (:username, :account, :password)");
    query.bindValue(":username", username);
    query.bindValue(":account", account);
    query.bindValue(":password", password);

    if (query.exec()) {
        ui->message->setText("注册成功");
        ui->message->setStyleSheet("color:green;");

        int userId = query.lastInsertId().toInt();
        User user(username, account, password);
        if (user.saveToDatabase(userId)) {
            qDebug() << "用户信息保存成功：" << user.username;
        } else {
            qDebug() << "用户信息保存失败";
        }

        emit registerSuccess();
        accept();
    } else {
        qDebug() << "注册失败，错误信息：" << query.lastError().text();
        ui->message->setText("注册失败，请稍后再试");
        ui->message->setStyleSheet("color:red;");
    }
}

void Register::on_cancelButton_clicked()
{
    emit registerCancel();
    this->close();
}
