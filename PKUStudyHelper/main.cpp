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
    QString courseTableSql = QString(
        "CREATE TABLE IF NOT EXISTS courses ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "account TEXT NOT NULL,"
        "weekday INTEGER NOT NULL,"
        "period INTEGER NOT NULL,"
        "course_name TEXT,"
        "classroom TEXT,"
        "teacher TEXT,"
        "remark TEXT,"
        "exam_info TEXT"
        ")");
    QString examTableSql = QString(
        "CREATE TABLE IF NOT EXISTS exams ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "account TEXT NOT NULL,"
        "course_name TEXT NOT NULL,"
        "exam_date TEXT NOT NULL,"
        "start_time TEXT NOT NULL,"
        "end_time TEXT NOT NULL,"
        "location TEXT NOT NULL"
        ")");
    QString assignmentsTableSql = QString(
        "CREATE TABLE IF NOT EXISTS assignments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "account TEXT NOT NULL,"
        "course_name TEXT NOT NULL,"
        "content TEXT NOT NULL,"
        "deadline TEXT NOT NULL,"
        "done INTEGER DEFAULT 0"
        ")");
    QSqlQuery userQuery;
    if (!userQuery.exec(userTableSql)) {
        qDebug() << "user table creation error";
    } else {
        qDebug() << "user table creation success";
    }
    // 开发阶段先删除旧表（可选）
    QSqlQuery().exec("DROP TABLE IF EXISTS courses");
    QSqlQuery().exec("DROP TABLE IF EXISTS exams");

    // 创建课程表
    QSqlQuery createQuery;
    if (!createQuery.exec(courseTableSql)) {
        qDebug() << "创建课程表失败：" << createQuery.lastError().text();
    }
    QSqlQuery examQuery;
    if (!examQuery.exec(examTableSql)) {
        qDebug() << "考试表创建失败：" << examQuery.lastError().text();
    }
    QSqlQuery assignmentQuery;
    if (!assignmentQuery.exec(assignmentsTableSql)) {
        qDebug() << "作业表创建失败:" << assignmentQuery.lastError().text();
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createDatabase();
    QSqlQuery query;
    QString account="2400013320";
    query.prepare("DELETE FROM user WHERE account=:account");
    query.bindValue(":account",account);
    if(!query.exec()){
        qDebug() << "删除用户失败:" << query.lastError().text();
    }
    else
    {
        qDebug() << "";
    }
    LoginDialog loginDialog;
    int result=loginDialog.exec();
    if(result==QDialog::Accepted){
        QSqlQuery query;
        query.exec("ALTER TABLE user ADD COLUMN json_tasks_content TEXT");
        MainWindow w;
        w.show();
        return a.exec();
    }
    else{
        return 0;
    }
}
