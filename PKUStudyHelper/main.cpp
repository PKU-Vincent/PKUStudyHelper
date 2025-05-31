#include "mainwindow.h"
#include"logindialog.h"
#include"UserInfo.h"
#include <QApplication>
#include<QSqlDatabase>

QSqlDatabase db;
QJsonObject data;
User current_user;

void createDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pku_study_helper.db");
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    }

    // 创建 user 表
    QString userTableSql = QString("CREATE TABLE IF NOT EXISTS user ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username NTEXT UNIQUE NOT NULL,"
                                   "account NTEXT UNIQUE NOT NULL,"
                                   "password NTEXT NOT NULL"
                                   ")");
    QSqlQuery userQuery;
    if (!userQuery.exec(userTableSql)) {
        qDebug() << "user table creation error";
    } else {
        qDebug() << "user table creation success";
    }

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createDatabase();
    LoginDialog loginDialog;
    int result=loginDialog.exec();
    if(result==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }
    else{
        return 0;
    }
}
