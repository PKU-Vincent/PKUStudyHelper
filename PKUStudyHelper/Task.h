#ifndef TASK_H
#define TASK_H
#include<QString>

class task{
public:
    QString taskname;
    QString starttime;
    bool is_ddl;
    QString ddl;
    bool finished=false;
    task(QString n,QString t,bool i=false,QString d=""):taskname(n),starttime(t),is_ddl(i),ddl(d){};
    ~task();
};

#endif // TASK_H
