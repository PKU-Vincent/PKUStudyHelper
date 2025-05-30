#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){};

private:
    QListWidget *navList;
    QStackedWidget *stackedWidget;
    QPushButton *addCourseButton;

    void setupUI();
    void setupConnections();
    QWidget* createAddCoursePage();

private slots:
    void handleNavigation(int index);
    void showAddCoursePage();
    void handleCourseClicked(const QString& courseName);
    void showContextMenu(const QPoint &pos);
};

#endif // MAINWINDOW_H
