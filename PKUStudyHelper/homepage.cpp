#include"homepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QFont>

HomePage::HomePage(const QString& username, QWidget *parent) : QWidget(parent) {
    // 主垂直布局（欢迎语 + 内容区域）
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);  // 设置部件间距
    mainLayout->setContentsMargins(20, 20, 20, 20);  // 设置边距

    // 欢迎语区域
    QTextBrowser *greetingBrowser = new QTextBrowser(this);
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

    QPushButton *viewScheduleButton = new QPushButton("查看完整课程表", this);
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

    QTableWidget *ddlTable = new QTableWidget(3, 3, this);
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

    QListWidget *todoList = new QListWidget(this);
    todoList->setStyleSheet(
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
    taskLayout->addWidget(todoList);

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
