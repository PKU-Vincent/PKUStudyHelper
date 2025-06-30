#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QSet>
#include "MiniTaskPage.h"
#include "HomePage.h"
#include "TaskPage.h"
#include "classpage.h"
#include "CoursePageTemplate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void on_item_clicked(QListWidgetItem *item);

private:
    void setupUI();

    Ui::MainWindow *ui = nullptr;

    QListWidget *navList = nullptr;
    QStackedWidget *stackedWidget = nullptr;
};

#endif // MAINWINDOW_H
