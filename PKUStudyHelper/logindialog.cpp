#include "logindialog.h"
#include "ui_logindialog.h"
#include"register.h"
#include<QFile>
#include<QDataStream>
#include<QDebug>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->registerbutton,&QPushButton::clicked,this,&LoginDialog::on_registerButton_clicked);
    connect(ui->loginbutton,&QPushButton::clicked,this,&LoginDialog::on_loginButton_clicked);
    initUserDatabase();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_registerButton_clicked()
{
    Register registerWindow;
    registerWindow.exec();
}

void LoginDialog::on_loginButton_clicked()
{
    QString username=ui->account->text();
    QString password=ui->password->text();

    if(!userDatabase.contains(username)){
        ui->label->setText("账号不存在");
        ui->label->setStyleSheet("color:red;");
    }
    else if(userDatabase[username].password!=password){
        ui->label->setText("密码错误");
        ui->label->setStyleSheet("color:red;");
    }
    else{
        ui->label->setText("登录成功");
        ui->label->setStyleSheet("color:green;");
        accept();
    }
}

void LoginDialog::initUserDatabase()
{
    QFile file("users.dat");
    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in >> userDatabase;
        file.close();
    }
    else{
        ;
    }
}
