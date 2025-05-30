#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDateTime>

class task{
public:
    QString taskname;
    QString starttime;
    bool is_ddl;
    QString ddl;
    bool finished = false;

    task(QString n, QString t, bool i = false, QString d = "")
        : taskname(n), starttime(t), is_ddl(i), ddl(d) {}
    ~task() {}

    // 判断任务是否已完成
    bool isFinished() const {
        return finished;
    }

    // 标记任务为已完成
    void markAsFinished() {
        finished = true;
    }

    // 计算距离截止日期的天数
    int daysToDDL() const {
        if (!is_ddl) return -1;
        QDateTime ddlTime = QDateTime::fromString(ddl, "yyyy-MM-dd hh:mm:ss");
        QDateTime currentTime = QDateTime::currentDateTime();
        return currentTime.daysTo(ddlTime);
    }
};

#endif // TASK_H
