#include "MainWindow.h"
#include "HomePage.h"
#include "SetNewClass.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>
#include "Task.h"  // 确保包含任务类定义

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
    navList->addItem("我的主页");
    navList->addItem("我的任务");
    navList->addItem("我的课程");

    // 添加课程按钮作为列表项
    QListWidgetItem *addCourseItem = new QListWidgetItem("+ 添加课程");
    QFont addFont;
    addFont.setPointSize(8);
    addFont.setItalic(true);
    addCourseItem->setFont(addFont);
    navList->addItem(addCourseItem);

    navLayout->addWidget(navList);
    navLayout->addStretch(1);
    navWidget->setFixedWidth(180);

    // 页面切换区域
    stackedWidget = new QStackedWidget(this);

    // 初始化任务数据
    QList<task> tasks;
    tasks.append(task("完成作业", "2024-05-31", true, "2024-06-02"));
    tasks.append(task("阅读书籍", "2024-05-31", false));
    tasks.append(task("提交报告", "2024-05-31", true, "2024-06-05"));

    // 创建主页并传入任务数据
    HomePage *homePage = new HomePage("小北", tasks, this);
    connect(homePage, &HomePage::courseClicked, this, &MainWindow::handleCourseClicked);
    stackedWidget->addWidget(homePage); // index 0

    // 创建其他页面
    QWidget *taskPage = new QWidget(this);
    QLabel *taskLabel = new QLabel("这是任务主页", taskPage);
    QVBoxLayout *taskLayout = new QVBoxLayout(taskPage);
    taskLayout->addWidget(taskLabel);
    stackedWidget->addWidget(taskPage); // index 1

    mainLayout->addWidget(navWidget);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setStretch(0, 0);
    mainLayout->setStretch(1, 1);
    setCentralWidget(central);

    connect(navList, &QListWidget::currentRowChanged, this, &MainWindow::handleNavigation);
    navList->setCurrentRow(0);

    // 右键菜单删除
    navList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(navList, &QListWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
}

void MainWindow::showAddCoursePage() {
    SetNewClass *setNewClassWidget = new SetNewClass(this);
    connect(setNewClassWidget, &SetNewClass::courseCreated, this, &MainWindow::handleCourseClicked);
    stackedWidget->addWidget(setNewClassWidget);
    stackedWidget->setCurrentWidget(setNewClassWidget);
}

void MainWindow::handleNavigation(int index) {
    if (index == 0) {
        stackedWidget->setCurrentIndex(0);
    } else if (index == 1) {
        stackedWidget->setCurrentIndex(1);
    } else if (navList->item(index)->text() == "+ 添加课程") {
        showAddCoursePage();
    } else {
        int pageIndex = stackedWidget->count() - (navList->count() - index);
        if (pageIndex >= 0 && pageIndex < stackedWidget->count()) {
            stackedWidget->setCurrentIndex(pageIndex);
        }
    }
}


void MainWindow::handleCourseClicked(const QString &courseName) {
    QWidget *coursePage = new QWidget(this);
    QLabel *label = new QLabel("这是课程主页：" + courseName, coursePage);
    QVBoxLayout *layout = new QVBoxLayout(coursePage);
    layout->addWidget(label);
    coursePage->setLayout(layout);

    stackedWidget->addWidget(coursePage);

    QListWidgetItem *courseItem = new QListWidgetItem("| " + courseName);
    QFont font = courseItem->font();
    font.setPointSize(12);
    courseItem->setFont(font);

    // 插入到“添加课程”前
    navList->insertItem(navList->count() - 1, courseItem);
    navList->setCurrentItem(courseItem);
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QListWidgetItem *item = navList->itemAt(pos);
    if (!item || item->text() == "我的主页" || item->text() == "我的任务" || item->text() == "我的课程" || item->text() == "+ 添加课程")
        return;

    QMenu contextMenu;
    QAction *deleteAction = contextMenu.addAction("删除课程");
    QAction *selectedAction = contextMenu.exec(navList->mapToGlobal(pos));

    if (selectedAction == deleteAction) {
        int row = navList->row(item);
        navList->takeItem(row);
        int pageIndex = stackedWidget->currentIndex();
        QWidget *widget = stackedWidget->widget(pageIndex);
        stackedWidget->removeWidget(widget);
        widget->deleteLater();
        navList->setCurrentRow(0); // 返回主页
    }
}


