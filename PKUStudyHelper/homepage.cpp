#include "homepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTime>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QLabel>
#include <QPalette>
#include <QPixmap>

HomePage::HomePage(const QString& username, const QString& account, QWidget *parent)
    : QWidget(parent), userName(username), userAccount(account)
{
    // ========== 1. 全局背景设置（笔记本背景） ==========
    QPalette globalPalette = this->palette();
    QPixmap bgPixmap(":/new/prefix1/纸质背景.jpg");
    if (!bgPixmap.isNull()) {
        // 让背景图自适应窗口大小，保持比例并平铺
        bgPixmap = bgPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        globalPalette.setBrush(QPalette::Window, QBrush(bgPixmap));
        this->setPalette(globalPalette);
        this->setAutoFillBackground(true);
    } else {
        qDebug() << "背景图加载失败";
    }

    // ========== 2. 主布局初始化 ==========
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // ---------- 欢迎语区域 ----------
    greetingBrowser = new QTextBrowser(this);
    QString greetingContent = getGreetingText(userName) + "\n" + getRandomQuote();
    greetingBrowser->setText(greetingContent);
    greetingBrowser->setStyleSheet(R"(
        font-family: 'Microsoft YaHei', sans-serif;
        font-size: 18px;
        font-weight: bold;
        color: #333333;
        background-color: rgba(255, 255, 255, 0.8); /* 半透明白底 */
        border-radius: 8px;
        padding: 15px;
    )");
    greetingBrowser->setMaximumHeight(80);
    mainLayout->addWidget(greetingBrowser);

    // ---------- 内容区域（课程表 + 任务区） ----------
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(20);
    mainLayout->addLayout(contentLayout);

    // ========== 3. 左侧课程表（填满空间） ==========
    QVBoxLayout *courseLayout = new QVBoxLayout();
    contentLayout->addLayout(courseLayout, 1);

    QLabel *courseLabel = new QLabel("今日课程", this);
    QString labelStyle = R"(
        font-family: 'Microsoft YaHei', sans-serif;
        font-size: 16px;
        font-weight: bold;
        color: #333333;
        margin-left: 10px;
        margin-bottom: 10px;
    )";
    courseLabel->setStyleSheet(labelStyle);
    courseLayout->addWidget(courseLabel);

    courseTable = new QTableWidget(0, 3, this);
    courseTable->setHorizontalHeaderLabels({"时间", "课程", "教室"});
    courseTable->setStyleSheet(R"(
        QTableWidget {
            font-family: 'Microsoft YaHei', sans-serif;
            font-size: 14px;
            gridline-color: #e0e0e0;
            border: 1px solid #ccc;
            border-radius: 6px;
            background-color: rgba(255, 255, 255, 0.8); /* 半透明白底 */
        }
        QHeaderView::section {
            background-color: #f0f0f0;
            font-weight: bold;
            padding: 8px;
            border: none;
            border-radius: 6px 6px 0 0;
        }
        QTableWidget::item {
            padding: 10px;
            border-bottom: 1px solid #e0e0e0;
        }
    )");
    // 让课程表填满父布局
    courseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    courseTable->verticalHeader()->setVisible(false);
    courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    courseLayout->addWidget(courseTable, 1); // 添加 stretch 因子，让课程表填满垂直空间

    // ========== 4. 右侧任务区（表格透明化） ==========
    QVBoxLayout *taskLayout = new QVBoxLayout();
    contentLayout->addLayout(taskLayout, 1);

    QLabel *miniTaskLabel = new QLabel("我的任务", this);
    miniTaskLabel->setStyleSheet(labelStyle);
    taskLayout->addWidget(miniTaskLabel);

    // 任务区表格透明化
    miniTaskPage = new MiniTaskPage(this, userAccount);
    miniTaskPage->setStyleSheet(R"(
        QTableWidget {
            background-color: transparent; /* 表格背景透明 */
            gridline-color: #e0e0e0;
            font-family: 'Microsoft YaHei', sans-serif;
            font-size: 14px;
        }
        QHeaderView::section {
            background-color: rgba(255, 255, 255, 0.8); /* 半透明白底 */
            font-weight: bold;
            padding: 8px;
            border: none;
            border-radius: 6px 6px 0 0;
        }
        QTableWidget::item {
            padding: 10px;
            border-bottom: 1px solid #e0e0e0;
            background-color: transparent; /* 单元格背景透明 */
        }
    )");
    taskLayout->addWidget(miniTaskPage, 1); // 添加 stretch 因子，让任务区填满垂直空间

    // ========== 5. 加载今日课程 ==========
    loadTodayCourses();
}

QString HomePage::getGreetingText(const QString& username)  //根据时间获得对应的问候语
{
    QTime currentTime = QTime::currentTime();
    QString greeting;
    if (currentTime.hour() < 12) {
        greeting = "早上好";
    } else if (currentTime.hour() < 18) {
        greeting = "下午好";
    } else {
        greeting = "晚上好";
    }
    return greeting +  "！";
}

QString HomePage::getRandomQuote()  //随机获得一句心灵鸡汤
{
    QStringList quotes = {
        "又是美好的一天，加油！",
        "梦想不会逃跑，逃跑的只有自己。",
        "你今天学习了吗？",
        "永远相信美好的事情即将发生。"
    };

    static bool seedInitialized = false;
    if (!seedInitialized) {
        srand(QTime::currentTime().msec());
        seedInitialized = true;
    }
    int index = rand() % quotes.size();
    return quotes.at(index);
}

void HomePage::loadTodayCourses()  //加载今日课程
{
    static const QList<QPair<QTime, QTime>> periodRanges = {
        {QTime(8, 0), QTime(8, 50)},
        {QTime(9, 0), QTime(9, 50)},
        {QTime(10, 10), QTime(11, 0)},
        {QTime(11, 10), QTime(12, 0)},
        {QTime(13, 0), QTime(13, 50)},
        {QTime(14, 0), QTime(14, 50)},
        {QTime(15, 10), QTime(16, 0)},
        {QTime(16, 10), QTime(17, 0)},
        {QTime(18, 40), QTime(19, 30)},
        {QTime(19, 40), QTime(20, 30)},
        {QTime(20, 40), QTime(21, 30)}
    };

    static const QStringList periodTimeStr = {
        "8:00-8:50", "9:00-9:50", "10:10-11:00", "11:10-12:00", "13:00-13:50",
        "14:00-14:50", "15:10-16:00", "16:10-17:00", "18:40-19:30",
        "19:40-20:30", "20:40-21:30"
    };

    QTime now = QTime::currentTime();

    int qtWeekDay = QDate::currentDate().dayOfWeek();
    int dbWeekDay = (qtWeekDay == 7) ? 0 : qtWeekDay;

    QSqlQuery query;
    query.prepare("SELECT period, course_name, classroom FROM courses WHERE account = :account AND weekday = :weekday ORDER BY period ASC");
    query.bindValue(":account", userAccount);
    query.bindValue(":weekday", dbWeekDay);
    if (!query.exec()) {
        qDebug() << "查询今日课程失败:" << query.lastError();
        return;
    }

    QMap<int, QPair<QString, QString>> courseMap;
    while (query.next()) {
        int period = query.value("period").toInt();
        QString name = query.value("course_name").toString();
        QString classroom = query.value("classroom").toString();
        courseMap[period] = qMakePair(name, classroom);
    }

    courseTable->setRowCount(11);
    for (int i = 0; i < 11; ++i) {
        int periodNum = i + 1;
        QString timeText = QString("第%1节 %2").arg(periodNum).arg(periodTimeStr[i]);

        QTableWidgetItem *timeItem = new QTableWidgetItem(timeText);
        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QTableWidgetItem *roomItem = new QTableWidgetItem();

        if (courseMap.contains(periodNum)) {
            nameItem->setText(courseMap[periodNum].first);
            roomItem->setText(courseMap[periodNum].second);
        }

        if (now >= periodRanges[i].first && now <= periodRanges[i].second) {
            QColor highlightColor = QColor(200, 255, 200);
            timeItem->setBackground(highlightColor);
            nameItem->setBackground(highlightColor);
            roomItem->setBackground(highlightColor);
        }

        courseTable->setItem(i, 0, timeItem);
        courseTable->setItem(i, 1, nameItem);
        courseTable->setItem(i, 2, roomItem);
    }
}
