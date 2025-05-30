#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDateTime>
#include<QTime>

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(const QString& username, QWidget *parent = nullptr);

signals:
    void courseClicked(const QString& courseName);

private slots:
    void handleCourseClicked(QListWidgetItem* item);

private:
    QString getGreetingText(const QString& username);
    QString getRandomQuote();

    QTextBrowser *greetingBrowser;
    QPushButton *viewScheduleButton;
    QListWidget *todayCoursesList;
    QListWidget *todayTasksList;
};
#endif // HOMEPAGE_H
