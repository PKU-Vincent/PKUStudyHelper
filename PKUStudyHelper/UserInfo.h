#ifndef USERINFO_H
#define USERINFO_H
#include<QString>
#include<QList>
#include"CourseInfo.h"
#include"Task.h"
#include<QDataStream>

class User{
public:
    QString username;
    QString account;
    QString password;
    QList<Course> courses;
    QList<task> tasks;
    QList<task> ddls;
    User(QString n,QString a,QString p):username(n),account(a),password(p){}
    ~User();
};

#endif // USERINFO_H
