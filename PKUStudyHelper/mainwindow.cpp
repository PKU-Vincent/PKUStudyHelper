#include "mainwindow.h"
#include "HomePage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QSet>
#include "MiniTaskPage.h"
#include "classpage.h"
#include "UserInfo.h"
#include "TaskPage.h"
#include "coursepagetemplate.h"

extern User current_user;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
}

void MainWindow::setupUI() {
    setMinimumSize(1200, 800);

    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // 左侧导航栏部分
    QWidget *navWidget = new QWidget(this);
    QVBoxLayout *navLayout = new QVBoxLayout(navWidget);

    navList = new QListWidget(this);
    navList->setStyleSheet(R"(
        QListWidget {
            border: none;
            font-size: 14px;
        }
        QListWidget::item {
            padding: 6px 12px;
        }
    )");

    // 添加基本导航项
    // 添加“我的主页”项并设置图标
    QListWidgetItem *homeItem = new QListWidgetItem("我的主页");
    QFont font1 = homeItem->font();
    font1.setPointSize(14);
    homeItem->setFont(font1);
    homeItem->setIcon(QIcon(":/new/prefix1/主页图标.jpg"));
    navList->addItem(homeItem);

    // 添加“我的任务”项并设置图标
    QListWidgetItem *taskItem = new QListWidgetItem("我的任务");
    QFont font2 = taskItem->font();
    font2.setPointSize(14);
    taskItem->setFont(font2);
    taskItem->setIcon(QIcon(":/new/prefix1/任务图标.jpg"));
    navList->addItem(taskItem);

    // 添加“我的课程”项并设置图标
    QListWidgetItem *courseItem = new QListWidgetItem("我的课程");
    QFont font3 = courseItem->font();
    font3.setPointSize(14);
    courseItem->setFont(font3);
    courseItem->setIcon(QIcon(":/new/prefix1/课程图标.jpg"));
    navList->addItem(courseItem);

    connect(navList, &QListWidget::itemClicked, this, &MainWindow::on_item_clicked);

    // 页面切换区域
    stackedWidget = new QStackedWidget(this);



    HomePage *homePage = new HomePage(current_user.username, current_user.account, this);
    stackedWidget->addWidget(homePage); // index 0

    TaskPage *taskPage = new TaskPage(this, current_user.account);
    stackedWidget->addWidget(taskPage); // index 1

    ClassPage *classPage = new ClassPage(current_user.account);
    stackedWidget->addWidget(classPage); // index 2

    connect(taskPage,&TaskPage::tasksChanged,homePage,&HomePage::refreshTasks);
    // 加载课程信息并添加课程主页页面
    QSqlQuery query;
    query.prepare("SELECT DISTINCT course_name FROM courses WHERE account = :account");
    query.bindValue(":account", current_user.account);
    if (!query.exec()) {
        qDebug() << "加载课程列表失败：" << query.lastError().text();
    } else {
        QSet<QString> courseSet;
        while (query.next()) {
            QString courseName = query.value(0).toString();
            if (!courseSet.contains(courseName)) {
                courseSet.insert(courseName);
                CoursePageTemplate *coursePage = new CoursePageTemplate(current_user.account, " "+courseName, this);
                stackedWidget->addWidget(coursePage);
                navList->addItem(courseName);  // 加入导航栏
                connect(coursePage, &CoursePageTemplate::assignmentsChanged,
                        taskPage, &TaskPage::refreshTasks);
                connect(coursePage, &CoursePageTemplate::assignmentsChanged,
                        homePage, &HomePage::refreshTasks);
            }
        }
    }

    navLayout->addWidget(navList);
    navLayout->addStretch();
    navWidget->setFixedWidth(180);

    mainLayout->addWidget(navWidget);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setStretch(0, 0);
    mainLayout->setStretch(1, 1);

    setCentralWidget(central);

    navList->setCurrentRow(0);
}

void MainWindow::on_item_clicked(QListWidgetItem *item)
{
    int index = navList->row(item);
    stackedWidget->setCurrentIndex(index);
}
