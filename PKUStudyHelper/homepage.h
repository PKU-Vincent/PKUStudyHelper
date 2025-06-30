#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QTextBrowser>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>

#include "MiniTaskPage.h"
class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(const QString& username, const QString& account, QWidget *parent = nullptr);

signals:
    void courseClicked(const QString& courseName);

public slots:
    void refreshTasks() { miniTaskPage->loadTasks(); }

private:
    QString userName;
    QString userAccount;

    QTextBrowser *greetingBrowser;

    QTableWidget *courseTable;
    QPushButton *viewScheduleButton;

    MiniTaskPage *miniTaskPage;

    QString getGreetingText(const QString& username);
    QString getRandomQuote();

    void loadTodayCourses();
};

#endif // HOMEPAGE_H
