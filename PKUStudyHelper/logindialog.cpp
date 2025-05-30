#include "logindialog.h"
#include "ui_logindialog.h"
#include"Register.h"
#include<QDebug>
#include<QGraphicsDropShadowEffect>

extern QSqlDatabase db;

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3,0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);

    connect(ui->registerbutton,&QPushButton::clicked,this,&LoginDialog::on_registerButton_clicked);
    connect(ui->loginButton,&QPushButton::clicked,this,&LoginDialog::on_loginButton_clicked);
    
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_registerButton_clicked()
{
    Register registerWindow;
    connect(&registerWindow, &Register::registerSuccess, this, &LoginDialog::on_register_success);
    connect(&registerWindow, &Register::registerCancel, this, &LoginDialog::on_register_cancel);
    registerWindow.exec();
}

void LoginDialog::on_loginButton_clicked()
{
    QString account=ui->account->text();
    QString password=ui->password->text();
    if(account.isEmpty()||password.isEmpty())
    {
        ui->label->setText("账号或密码不能为空");
        ui->label->setStyleSheet("color:red;");
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE account = :account");
    query.bindValue(":account", account);
    if(!query.exec())
        return;
        if (!query.next()) {
            // 没有找到该账号
            ui->label->setText("账号不存在");
            qDebug()<<"错误信息："<<query.lastError().text();
            ui->label->setStyleSheet("color:red;");
        } else {
            // 账号存在，检查密码
            query.prepare("SELECT * FROM user WHERE account = :account AND password = :password");
            query.bindValue(":account", account);
            query.bindValue(":password", password);
            if (query.exec() && query.next()) {
                // 登录成功
                ui->label->setText("登录成功");
                ui->label->setStyleSheet("color:green;");
                accept();
            } else {
                // 密码错误
                ui->label->setText("密码错误");
                ui->label->setStyleSheet("color:red;");
            }
        }
}

void LoginDialog::on_register_cancel()
{
    ui->label->setText("注册已取消");
    ui->label->setStyleSheet("color:black;");
}
void LoginDialog::on_register_success()
{
    ui->label->setText("注册成功，请登录");
    ui->label->setStyleSheet("color:green;");
}

