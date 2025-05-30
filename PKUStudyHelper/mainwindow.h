
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include "Task.h"
#include"CourseInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){};

private slots:
    void handleNavigation(int index);
    void handleCourseClicked(const QString &courseName);
    void showContextMenu(const QPoint &pos);
    void showAddCoursePage();
private:
    void setupUI();
    Course* getCourseByName(const QString& courseName);
    Ui::MainWindow *ui;
    QListWidget *navList;
    QStackedWidget *stackedWidget;
    QList<task> tasks;  // 新增：存储所有任务
};

#endif // MAINWINDOW_H
