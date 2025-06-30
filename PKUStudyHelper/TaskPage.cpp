#include "TaskPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMenu>
#include <QAction>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFont>
#include <QPalette>
#include <QPixmap>
#include <QDebug>

TaskPage::TaskPage(QWidget *parent, const QString &account) : QWidget(parent), userAccount(account) {
    // ========== 1. 全局纸质背景设置 ==========
    QPalette globalPalette = this->palette();
    QPixmap bgPixmap(":/new/prefix1/纸质背景.jpg");
    if (!bgPixmap.isNull()) {
        bgPixmap = bgPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        globalPalette.setBrush(QPalette::Window, QBrush(bgPixmap));
        this->setPalette(globalPalette);
        this->setAutoFillBackground(true);
    }

    // ========== 2. 创建任务输入区域 ==========
    QLabel *deadlineLabel = new QLabel("设置截止日期:", this);
    deadlineLabel->setStyleSheet(R"(
        font-size: 18px;
        background-color: rgba(255, 255, 255, 0.7);
        padding: 5px 10px;
        border-radius: 4px;
    )");

    dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setStyleSheet(R"(
        font-size: 18px;
        background-color: rgba(255, 255, 255, 0.7);
        padding: 5px;
        border: 1px solid #cccccc;
        border-radius: 4px;
    )");

    // 为QCalendarWidget单独设置样式，解决反色问题
    dateEdit->setStyleSheet(R"(
        /* QDateEdit 本身的样式 */
        QDateEdit {
            font-size: 18px;
            background-color: rgba(255, 255, 255, 0.7);
            padding: 5px;
            border: 1px solid #cccccc;
            border-radius: 4px;
        }
        /* 下拉按钮样式 */
        QDateEdit::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: right;
            width: 30px;
            border-left: 1px solid #cccccc;
            border-top-right-radius: 4px;
            border-bottom-right-radius: 4px;
        }
        /* 日历控件整体样式 */
        QCalendarWidget {
            background-color: white; /* 日历背景设为白色 */
            color: #333333;          /* 日期文字颜色 */
            border: 1px solid #cccccc;
            border-radius: 4px;
        }
        /* 日历表头（星期、月份） */
        QCalendarWidget QHeaderView {
            background-color: #f0f0f0; /* 表头背景 */
            color: #333333;            /* 表头文字颜色 */
            border-bottom: 1px solid #cccccc;
        }
        /* 日期项通用样式 */
        QCalendarWidget QAbstractItemView {
            selection-background-color: #4CAF50; /* 选中日期的背景 */
            selection-color: white;              /* 选中日期的文字颜色 */
        }
        /* 周末日期（可根据需求调整，比如周六日文字颜色） */
        QCalendarWidget QAbstractItemView:disabled {
            color: #ff0000; /* 这里仅示例，可改为合理颜色 */
        }
        /* 月份切换按钮 */
        QCalendarWidget QToolButton {
            color: #333333; /* 按钮文字颜色 */
            background-color: #f0f0f0; /* 按钮背景 */
            border: none;
        }
        QCalendarWidget QToolButton:hover {
            background-color: #e0e0e0; /* 鼠标悬浮时的按钮背景 */
        }
    )");

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("任务名称");
    nameEdit->setStyleSheet(R"(
        font-size: 18px;
        background-color: rgba(255, 255, 255, 0.7);
        padding: 5px;
        border: 1px solid #cccccc;
        border-radius: 4px;
    )");

    addButton = new QPushButton("创建任务", this);
    addButton->setStyleSheet(R"(
        font-size: 18px;
        background-color: rgba(76, 175, 80, 0.8);
        color: white;
        padding: 5px 15px;
        border-radius: 4px;
        border: none;
    )");
    addButton->setCursor(Qt::PointingHandCursor);

    // ========== 3. 任务列表区域 ==========
    taskList = new QListWidget(this);
    taskList->setStyleSheet(R"(
        QListWidget {
            font-size: 18px;
            background-color: rgba(255, 255, 255, 0.7);
            border: 1px solid #cccccc;
            border-radius: 6px;
            padding: 5px;
        }
        QListWidget::item {
            padding: 8px;
            border-bottom: 1px solid #eeeeee;
        }
        QListWidget::item:selected {
            background-color: rgba(33, 150, 243, 0.3);
            color: #333333;
        }
    )");

    // ========== 4. 布局设置 ==========
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(deadlineLabel);
    inputLayout->addWidget(dateEdit);
    inputLayout->addWidget(nameEdit);
    inputLayout->addWidget(addButton);
    inputLayout->setSpacing(10);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(taskList);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    setLayout(mainLayout);

    // ========== 5. 信号与槽连接 ==========
    connect(addButton, &QPushButton::clicked, this, &TaskPage::addTask);
    connect(taskList, &QListWidget::customContextMenuRequested, this, &TaskPage::showContextMenu);
    taskList->setContextMenuPolicy(Qt::CustomContextMenu);

    loadTasks();
}


void TaskPage::addTask() {   //添加任务
    QString date = dateEdit->date().toString("yyyy-MM-dd");
    QString name = nameEdit->text();
    if (date.isEmpty() || name.isEmpty()) return;

    QJsonObject newTask;
    newTask["deadline"] = date;
    newTask["name"] = name;
    newTask["done"] = false;

    QSqlQuery query;
    query.prepare("SELECT json_tasks_content FROM user WHERE account = :account");
    query.bindValue(":account", userAccount);
    query.exec();

    QJsonArray array;
    if (query.next()) {
        QString jsonStr = query.value(0).toString();
        if (!jsonStr.isEmpty()) {
            array = QJsonDocument::fromJson(jsonStr.toUtf8()).array();
        }
    }
    array.append(newTask);
    saveTasks(getSortedTasks(array));
    nameEdit->clear();
    dateEdit->setDate(QDate::currentDate());
    loadTasks();
}

void TaskPage::loadTasks() {  //加载任务
    taskList->clear();
    dateEdit->setDate(QDate::currentDate());
    nameEdit->clear();

    QSqlQuery query;
    query.prepare("SELECT json_tasks_content FROM user WHERE account = :account");
    query.bindValue(":account", userAccount);
    query.exec();

    QMap<QString, QList<QListWidgetItem*>> categorizedItems;

    if (query.next()) {
        QString jsonStr = query.value(0).toString();
        if (!jsonStr.isEmpty()) {
            QJsonArray array = QJsonDocument::fromJson(jsonStr.toUtf8()).array();

            for (const QJsonValue &val : array) {
                QJsonObject obj = val.toObject();
                QString deadline = obj["deadline"].toString();
                QString name = obj["name"].toString();
                bool done = obj["done"].toBool();

                QString status = deadlineStatus(QDate::fromString(deadline, "yyyy-MM-dd"));
                QString text = deadline + " | " + name;

                QListWidgetItem *item = new QListWidgetItem(text);
                QFont font = item->font();
                font.setPointSize(16);
                if (done) {
                    font.setStrikeOut(true);
                }
                item->setFont(font);

                if (!done && status.contains("今天")) {
                    item->setForeground(QColor("red"));
                }

                QString category = done ? "已完成" : status.isEmpty() ? "其他任务" : status;
                categorizedItems[category].append(item);
            }
        }
    }

    for (const QString &category : {"今天截止 ⚠", "三天内截止", "一周内截止", "其他任务", "已完成"}) {
        if (categorizedItems.contains(category)) {
            QListWidgetItem *header = new QListWidgetItem("【" + category + "】");
            QFont headerFont;
            headerFont.setBold(true);
            headerFont.setPointSize(18);
            header->setFont(headerFont);
            header->setFlags(Qt::NoItemFlags);
            taskList->addItem(header);
            for (QListWidgetItem *item : categorizedItems[category]) {
                taskList->addItem(item);
            }
        }
        emit tasksChanged();
    }
}

void TaskPage::saveTasks(const QJsonArray &array) {  //储存任务
    QSqlQuery query;
    query.prepare("UPDATE user SET json_tasks_content = :json WHERE account = :account");
    query.bindValue(":json", QString(QJsonDocument(array).toJson()));
    query.bindValue(":account", userAccount);
    query.exec();
}

void TaskPage::showContextMenu(const QPoint &pos) {
    QListWidgetItem *item = taskList->itemAt(pos);
    if (!item || !item->flags().testFlag(Qt::ItemIsSelectable)) return;

    QMenu menu(this);
    QAction *doneAction = menu.addAction("已完成");
    QAction *deleteAction = menu.addAction("删除");
    QAction *selected = menu.exec(taskList->viewport()->mapToGlobal(pos));

    if (selected == doneAction) markTaskDone();
    else if (selected == deleteAction) deleteTask();
}

void TaskPage::markTaskDone() {   //标记任务已完成
    int row = taskList->currentRow();
    if (row < 0) return;

    QSqlQuery query;
    query.prepare("SELECT json_tasks_content FROM user WHERE account = :account");
    query.bindValue(":account", userAccount);
    query.exec();

    if (query.next()) {
        QJsonArray array = QJsonDocument::fromJson(query.value(0).toString().toUtf8()).array();

        int actualRow = 0;
        for (int i = 0; i < taskList->count(); ++i) {
            QListWidgetItem *item = taskList->item(i);
            if (item->flags().testFlag(Qt::ItemIsSelectable)) {
                if (i == row) break;
                ++actualRow;
            }
        }

        if (actualRow < array.size()) {
            QJsonObject obj = array[actualRow].toObject();
            obj["done"] = true;
            array[actualRow] = obj;
            saveTasks(getSortedTasks(array));
            loadTasks();
        }
    }
}

void TaskPage::deleteTask() {   //删除任务
    int row = taskList->currentRow();
    if (row < 0) return;

    QSqlQuery query;
    query.prepare("SELECT json_tasks_content FROM user WHERE account = :account");
    query.bindValue(":account", userAccount);
    query.exec();

    if (query.next()) {
        QJsonArray array = QJsonDocument::fromJson(query.value(0).toString().toUtf8()).array();

        int actualRow = 0;
        for (int i = 0; i < taskList->count(); ++i) {
            QListWidgetItem *item = taskList->item(i);
            if (item->flags().testFlag(Qt::ItemIsSelectable)) {
                if (i == row) break;
                ++actualRow;
            }
        }

        if (actualRow < array.size()) {
            array.removeAt(actualRow);
            saveTasks(getSortedTasks(array));
            loadTasks();
        }
    }
}

QJsonArray TaskPage::getSortedTasks(const QJsonArray &array) {   //将任务按截止日期排序
    QList<QJsonObject> list;
    for (const QJsonValue &val : array) list.append(val.toObject());

    std::sort(list.begin(), list.end(), [](const QJsonObject &a, const QJsonObject &b) {
        if (a["done"].toBool() != b["done"].toBool())
            return !a["done"].toBool();
        return QDate::fromString(a["deadline"].toString(), "yyyy-MM-dd") < QDate::fromString(b["deadline"].toString(), "yyyy-MM-dd");
    });

    QJsonArray result;
    for (const QJsonObject &obj : list) result.append(obj);
    return result;
}

QString TaskPage::deadlineStatus(const QDate &date) {   //将任务按截止日期分类
    int days = QDate::currentDate().daysTo(date);
    if (days == 0) return "今天截止 ⚠";
    else if (days > 0 && days <= 3) return "三天内截止";
    else if (days > 3 && days <= 7) return "一周内截止";
    return "";
}
