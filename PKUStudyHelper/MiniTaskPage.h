#ifndef MINITASKPAGE_H
#define MINITASKPAGE_H

#include <QWidget>
#include <QListWidget>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <QMenu>
#include <QAction>

class MiniTaskPage : public QWidget {
    Q_OBJECT
public:
    explicit MiniTaskPage(QWidget *parent = nullptr, const QString &account = QString());
    void loadTasks();

private:
    QListWidget *taskList;
    QString userAccount;

    void saveTasks(const QJsonArray &array);
    void showContextMenu(const QPoint &pos);
    void markTaskDone();
    void deleteTask();
    QJsonArray getSortedTasks(const QJsonArray &array);
    QString deadlineStatus(const QDate &date);
};
#endif // MINITASKPAGE_H
