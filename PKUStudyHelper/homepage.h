#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include <QTimer>
#include "Task.h"

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(const QString& username, const QList<task>& tasks, QWidget *parent = nullptr);

signals:
    void courseClicked(const QString& courseName);

private slots:
    void handleCourseClicked(QListWidgetItem* item);
    void handleTaskFinished(QListWidgetItem* item);
    void showContextMenu(const QPoint &pos);
    void showDDLContextMenu(const QPoint &pos);
    void updateDDLStatus();

private:
    QString getGreetingText(const QString& username);
    QString getRandomQuote();

    void setupTaskList(const QList<task>& tasks);
    void setupDDLTable(const QList<task>& tasks);

    QTextBrowser *greetingBrowser;
    QPushButton *viewScheduleButton;
    QListWidget *todayTasksList;
    QTableWidget *ddlTable;
    QList<task> allTasks;
};

#endif // HOMEPAGE_H
