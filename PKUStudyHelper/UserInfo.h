#ifndef USERINFO_H
#define USERINFO_H
#include<QString>
#include<QList>
#include"MiniTaskPage.h"
#include<QDataStream>

class User{
public:
    QString username;
    QString account;
    QString password;
    User(QString n,QString a,QString p):username(n),account(a),password(p){}
    User(){}
    ~User(){};
};

#endif // USERINFO_H
