#include "mainwindow.h"
#include"logindialog.h"
#include <QApplication>
#include<QSqlDatabase>

QSqlDatabase db;

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

    // 创建 course 表
    QString courseTableSql = QString("CREATE TABLE IF NOT EXISTS course ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "user_id INTEGER NOT NULL,"
                                     "course_name NTEXT NOT NULL,"
                                     "FOREIGN KEY (user_id) REFERENCES user(id)"
                                     ")");
    QSqlQuery courseQuery;
    if (!courseQuery.exec(courseTableSql)) {
        qDebug() << "course table creation error";
    } else {
        qDebug() << "course table creation success";
    }

    // 创建 task 表
    QString taskTableSql = QString("CREATE TABLE IF NOT EXISTS task ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "user_id INTEGER NOT NULL,"
                                   "task_name NTEXT NOT NULL,"
                                   "FOREIGN KEY (user_id) REFERENCES user(id)"
                                   ")");
    QSqlQuery taskQuery;
    if (!taskQuery.exec(taskTableSql)) {
        qDebug() << "task table creation error";
    } else {
        qDebug() << "task table creation success";
    }

    // 创建 ddl 表
    QString ddlTableSql = QString("CREATE TABLE IF NOT EXISTS ddl ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "user_id INTEGER NOT NULL,"
                                  "ddl_name NTEXT NOT NULL,"
                                  "FOREIGN KEY (user_id) REFERENCES user(id)"
                                  ")");
    QSqlQuery ddlQuery;
    if (!ddlQuery.exec(ddlTableSql)) {
        qDebug() << "ddl table creation error";
    } else {
        qDebug() << "ddl table creation success";
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
