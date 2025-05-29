#include "register.h"
#include "ui_register.h"
#include<QFile>
#include<QDataStream>

Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_confirmButton_clicked()
{
    QString username=ui->newname->text();
    QString account=ui->newaccount->text();
    QString password=ui->newcode->text();
    QString confirmPassword=ui->confirmpassword->text();

    if(username.isEmpty()||password.isEmpty()){
        ui->message->setText("用户名或密码不能为空");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    if(password!=confirmPassword){
        ui->message->setText("两次输入的密码不一致");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    User newUser(username,account,password);
    QFile file("users.dat");
    QMap<QString,User> userDatabase;

    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in >> userDatabase;
        file.close();
    }

    if(userDatabase.contains(username)){
        ui->message->setText("用户名已存在");
        ui->message->setStyleSheet("color:red;");
        return;
    }

    userDatabase.insert(username,newUser);

    if(file.open(QIODevice::WriteOnly)){
        QDataStream out(&file);
        out<<userDatabase;
        file.close();
    }

    emit registerSuccess();
    close();
}

void Register::on_cancelButton_clicked()
{
    emit registerCancel();
    close();
}
