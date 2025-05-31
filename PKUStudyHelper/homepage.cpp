#include "homepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QFont>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QMenu>
#include<QLabel>
#include <QAction>


HomePage::HomePage(const QString& username, const QList<task>& tasks, QWidget *parent) : QWidget(parent) {
    allTasks = tasks;

    // 主垂直布局（欢迎语 + 内容区域）
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);  // 设置部件间距
    mainLayout->setContentsMargins(20, 20, 20, 20);  // 设置边距

    // 欢迎语区域
    greetingBrowser = new QTextBrowser(this);
    greetingBrowser->setText(getGreetingText(username) + "\n" + getRandomQuote());
    greetingBrowser->setStyleSheet(
        "font-family: 'Microsoft YaHei', sans-serif;"
        "font-size: 18px;"
        "font-weight: bold;"
        "color: #333333;"
        "background-color: #f5f5f5;"
        "border-radius: 8px;"
        "padding: 15px;"
        );
    greetingBrowser->setMaximumHeight(80);
    mainLayout->addWidget(greetingBrowser);

    // 内容区域（水平布局：课程表 | 任务栏）
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(20);
    mainLayout->addLayout(contentLayout);

    // 左侧：课程表区域
    QVBoxLayout *courseLayout = new QVBoxLayout();
    contentLayout->addLayout(courseLayout, 1);  // 权重 1

    QLabel *courseLabel = new QLabel("今日课程", this);
    courseLabel->setStyleSheet(
        "font-family: 'Microsoft YaHei', sans-serif;"
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #333333;"
        "margin-bottom: 10px;"
        );
    courseLayout->addWidget(courseLabel);

    QTableWidget *courseTable = new QTableWidget(5, 3, this);  // 5行3列
    courseTable->setHorizontalHeaderLabels({"时间", "课程", "教室"});
    courseTable->setStyleSheet(
        "QTableWidget {"
        "    font-family: 'Microsoft YaHei', sans-serif;"
        "    font-size: 14px;"
        "    gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "    background-color: #f0f0f0;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
        "QTableWidget::item {"
        "    padding: 8px;"
        "}"
        );
    courseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    courseTable->verticalHeader()->setVisible(false);
    courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 不可编辑
    courseLayout->addWidget(courseTable);

    viewScheduleButton = new QPushButton("查看完整课程表", this);
    viewScheduleButton->setStyleSheet(
        "QPushButton {"
        "    font-family: 'Microsoft YaHei', sans-serif;"
        "    font-size: 14px;"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );
    courseLayout->addWidget(viewScheduleButton);

    // 右侧：任务区域（DDL + To-do List）
    QVBoxLayout *taskLayout = new QVBoxLayout();
    contentLayout->addLayout(taskLayout, 1);  // 权重 1

    QLabel *taskLabel = new QLabel("今日任务", this);
    taskLabel->setStyleSheet(
        "font-family: 'Microsoft YaHei', sans-serif;"
        "font-size: 16px;"
        "font-weight: bold;"
        "color: #333333;"
        "margin-bottom: 10px;"
        );
    taskLayout->addWidget(taskLabel);

    // DDL 表格
    QLabel *ddlLabel = new QLabel("即将截止", this);
    ddlLabel->setStyleSheet(
        "font-family: 'Microsoft YaHei', sans-serif;"
        "font-size: 14px;"
        "font-weight: bold;"
        "color: #555555;"
        );
    taskLayout->addWidget(ddlLabel);

    ddlTable = new QTableWidget(0, 3, this);
    ddlTable->setHorizontalHeaderLabels({"截止时间", "任务", "状态"});
    ddlTable->setStyleSheet(
        "QTableWidget {"
        "    font-family: 'Microsoft YaHei', sans-serif;"
        "    font-size: 14px;"
        "    gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "    background-color: #f0f0f0;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
        "QTableWidget::item {"
        "    padding: 8px;"
        "}"
        );
    ddlTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ddlTable->verticalHeader()->setVisible(false);
    ddlTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskLayout->addWidget(ddlTable);

    // To-do List
    QLabel *todoLabel = new QLabel("待办事项", this);
    todoLabel->setStyleSheet(
        "font-family: 'Microsoft YaHei', sans-serif;"
        "font-size: 14px;"
        "font-weight: bold;"
        "color: #555555;"
        );
    taskLayout->addWidget(todoLabel);

    todayTasksList = new QListWidget(this);
    todayTasksList->setStyleSheet(
        "QListWidget {"
        "    font-family: 'Microsoft YaHei', sans-serif;"
        "    font-size: 14px;"
        "    border: 1px solid #e0e0e0;"
        "    border-radius: 5px;"
        "}"
        "QListWidget::item {"
        "    padding: 10px;"
        "    border-bottom: 1px solid #e0e0e0;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #d9edf7;"
        "}"
        );
    taskLayout->addWidget(todayTasksList);

    // 设置任务列表和 DDL 表格
    setupTaskList(tasks);
    setupDDLTable(tasks);

    // 连接右键菜单信号
    todayTasksList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(todayTasksList, &QListWidget::customContextMenuRequested, this, &HomePage::showContextMenu);

    // 为 DDL 表格设置右键菜单
    ddlTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ddlTable, &QTableWidget::customContextMenuRequested, this, &HomePage::showDDLContextMenu);

    // 定时更新 DDL 状态
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HomePage::updateDDLStatus);
    timer->start(60 * 1000); // 每分钟更新一次

    setLayout(mainLayout);
}

QString HomePage::getGreetingText(const QString& username) {
    QTime currentTime = QTime::currentTime();
    QString greeting;
    if (currentTime.hour() < 12)
        greeting = "早上好";
    else if (currentTime.hour() < 18)
        greeting = "下午好";
    else
        greeting = "晚上好";
    return greeting + ", " + username + "！";
}

QString HomePage::getRandomQuote() {
    QStringList quotes = {
        "又是美好的一天，加油！",
        "梦想不会逃跑，逃跑的只有自己。",
        "你今天学习了吗？",
        "永远相信美好的事情即将发生。"
    };

    static bool seedInitialized = false;
    if (!seedInitialized) {
        srand(QTime::currentTime().msec());  // 使用当前时间毫秒作为种子
        seedInitialized = true;
    }

    // 生成随机索引
    int index = rand() % quotes.size();
    return quotes.at(index);
}

void HomePage::handleCourseClicked(QListWidgetItem* item) {
    if (item) emit courseClicked(item->text());
}

void HomePage::handleTaskFinished(QListWidgetItem* item) {
    if (!item) return;
    QString taskName = item->text();
    for (auto& t : allTasks) {
        if (t.taskname == taskName) {
            t.markAsFinished();
            break;
        }
    }

    // 划上横线
    QFont font = item->font();
    font.setStrikeOut(true);
    item->setFont(font);

    // 移动到列表末尾
    QListWidgetItem *movedItem = todayTasksList->takeItem(todayTasksList->row(item));
    todayTasksList->addItem(movedItem);

    // 更新 DDL 表格
    for (int i = 0; i < ddlTable->rowCount(); ++i) {
        if (ddlTable->item(i, 1)->text() == taskName) {
            QFont ddlFont = ddlTable->item(i, 1)->font();
            ddlFont.setStrikeOut(true);
            ddlTable->item(i, 1)->setFont(ddlFont);
            ddlTable->item(i, 2)->setText("已完成");
            break;
        }
    }
}

void HomePage::showContextMenu(const QPoint &pos) {
    QListWidgetItem *item = todayTasksList->itemAt(pos);
    if (!item) return;

    QMenu contextMenu(this);
    QAction *finishAction = contextMenu.addAction("已完成");
    QAction *selectedAction = contextMenu.exec(todayTasksList->mapToGlobal(pos));

    if (selectedAction == finishAction) {
        handleTaskFinished(item);
    }
}

void HomePage::setupTaskList(const QList<task>& tasks) {
    for (const auto& t : tasks) {
        if (!t.is_ddl) {
            QListWidgetItem *item = new QListWidgetItem(t.taskname, todayTasksList);
            if (t.isFinished()) {
                QFont font = item->font();
                font.setStrikeOut(true);
                item->setFont(font);
            }
        }
    }
}

void HomePage::setupDDLTable(const QList<task>& tasks) {
    ddlTable->setRowCount(0);
    for (const auto& t : tasks) {
        if (t.is_ddl) {
            int row = ddlTable->rowCount();
            ddlTable->insertRow(row);
            ddlTable->setItem(row, 0, new QTableWidgetItem(t.ddl));
            QTableWidgetItem *taskItem = new QTableWidgetItem(t.taskname);
            if (t.isFinished()) {
                QFont font = taskItem->font();
                font.setStrikeOut(true);
                taskItem->setFont(font);
            }
            ddlTable->setItem(row, 1, taskItem);
            int days = t.daysToDDL();
            QString status;
            if (days == 0) {
                status = "今天截止！";
            } else if (days > 0 && days <= 3) {
                status = "三天内截止";
            } else if (days > 3 && days <= 7) {
                status = "一周内截止";
            } else if (days > 7) {
                status = "当前良好";
            } else {
                status = "已过期";
            }
            ddlTable->setItem(row, 2, new QTableWidgetItem(status));
        }
    }
}

void HomePage::updateDDLStatus() {
    for (int i = 0; i < ddlTable->rowCount(); ++i) {
        if (!ddlTable->item(i, 1) || ddlTable->item(i, 1)->text() == "已完成")
            continue;

        QString taskName = ddlTable->item(i, 1)->text();
        for (const auto& t : allTasks) {
            if (t.taskname == taskName) {
                int days = t.daysToDDL();
                QString status;
                if (days == 0) {
                    status = "今天截止！";
                } else if (days > 0 && days <= 3) {
                    status = "三天内截止";
                } else if (days > 3 && days <= 7) {
                    status = "一周内截止";
                } else if (days > 7) {
                    status = "当前良好";
                } else {
                    status = "已过期";
                }
                ddlTable->item(i, 2)->setText(status);
                break;
            }
        }
    }
}

void HomePage::showDDLContextMenu(const QPoint &pos) {
    QModelIndex index = ddlTable->indexAt(pos);
    if (!index.isValid()) return;

    QMenu contextMenu(this);
    QAction *finishAction = contextMenu.addAction("已完成");
    QAction *selectedAction = contextMenu.exec(ddlTable->mapToGlobal(pos));

    if (selectedAction == finishAction) {
        QString taskName = ddlTable->item(index.row(), 1)->text();

        // 更新任务状态
        for (auto& t : allTasks) {
            if (t.taskname == taskName && t.is_ddl) {
                t.markAsFinished();
                break;
            }
        }

        // 更新UI显示
        QFont font = ddlTable->item(index.row(), 1)->font();
        font.setStrikeOut(true);
        ddlTable->item(index.row(), 1)->setFont(font);
        ddlTable->item(index.row(), 2)->setText("已完成");

        // 移动到表格底部
        QTableWidgetItem *item0 = ddlTable->takeItem(index.row(), 0);
        QTableWidgetItem *item1 = ddlTable->takeItem(index.row(), 1);
        QTableWidgetItem *item2 = ddlTable->takeItem(index.row(), 2);

        ddlTable->removeRow(index.row());
        int newRow = ddlTable->rowCount();
        ddlTable->insertRow(newRow);
        ddlTable->setItem(newRow, 0, item0);
        ddlTable->setItem(newRow, 1, item1);
        ddlTable->setItem(newRow, 2, item2);
    }
}
