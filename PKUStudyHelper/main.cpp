#include "mainwindow.h"
#include"logindialog.h"
#include <QApplication>
#include<QSqlDatabase>

QSqlDatabase db;

void createDatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pku_study_helper.db");
    QString createsql = QString("CREATE TABLE IF NOT EXISTS user ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "username NTEXT UNIQUE NOT NULL,"
                                "account NTEXT UNIQUE NOT NULL,"
                                "password NTEXT NOT NULL"
                                ")");
    if(!db.open()){
        qDebug()<<"Database connection failed:"<<db.lastError().text();
    }
    QSqlQuery query;
    if(!query.exec(createsql)){
        qDebug()<<"table creat error";
    }
    else{
        qDebug()<<"table creat success";
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
