#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMenu>
#include <QAction>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QLabel>

class TaskPage : public QWidget {
    Q_OBJECT
public:
    TaskPage(QWidget *parent = nullptr, const QString &account = "");

private slots:
    void addTask();
    void showContextMenu(const QPoint &pos);
    void markTaskDone();
    void deleteTask();

public slots:
    void refreshTasks() { loadTasks(); }

signals:
    void tasksChanged(); // 方便任务主页同步

private:
    QString userAccount;
    QVBoxLayout *mainLayout;
    QDateEdit *dateEdit;
    QLineEdit *nameEdit;
    QPushButton *addButton;
    QListWidget *taskList;

    void loadTasks();
    void saveTasks(const QJsonArray &array);
    QJsonArray getSortedTasks(const QJsonArray &array);
    QString deadlineStatus(const QDate &date);
};

#endif
