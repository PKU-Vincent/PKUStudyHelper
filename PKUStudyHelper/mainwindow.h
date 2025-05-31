#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include<QCoreApplication>
#include<QProcess>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include "Task.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){};

private slots:
    void on_item_clicked(QListWidgetItem *item);
private:
    void setupUI();
    Ui::MainWindow *ui;
    QListWidget *navList;
    QStackedWidget *stackedWidget;
    QList<task> tasks;
    void updateScheduleUI(QJsonObject scheduleData);
    QJsonObject getScheduleFromPython(const QString& studentId, const QString& password);
    QVector<QMap<QString, QString>> jsonObjectToScheduleEntries(const QJsonObject& jsonObj);
};

#endif // MAINWINDOW_H
