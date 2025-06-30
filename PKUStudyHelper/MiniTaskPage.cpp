#include "MiniTaskPage.h"
#include <QFont>
#include <QColor>
#include<QVBoxLayout>

MiniTaskPage::MiniTaskPage(QWidget *parent, const QString &account)
    : QWidget(parent), userAccount(account)
{
    taskList = new QListWidget(this);
    taskList->setStyleSheet("font-size: 12px;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(taskList);
    setLayout(mainLayout);

    connect(taskList, &QListWidget::customContextMenuRequested, this, &MiniTaskPage::showContextMenu);
    taskList->setContextMenuPolicy(Qt::CustomContextMenu);

    loadTasks();
}

void MiniTaskPage::loadTasks()  //加载任务
{
    taskList->clear();

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
                font.setPointSize(12);
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
            headerFont.setPointSize(14);
            header->setFont(headerFont);
            header->setFlags(Qt::NoItemFlags);
            taskList->addItem(header);
            for (QListWidgetItem *item : categorizedItems[category]) {
                taskList->addItem(item);
            }
        }
    }
}

void MiniTaskPage::saveTasks(const QJsonArray &array)   //利用数据库储存任务
{
    QSqlQuery query;
    query.prepare("UPDATE user SET json_tasks_content = :json WHERE account = :account");
    query.bindValue(":json", QString(QJsonDocument(array).toJson(QJsonDocument::Compact)));
    query.bindValue(":account", userAccount);
    query.exec();
}

void MiniTaskPage::showContextMenu(const QPoint &pos)
{
    QListWidgetItem *item = taskList->itemAt(pos);
    if (!item || !item->flags().testFlag(Qt::ItemIsSelectable)) return;

    QMenu menu(this);
    QAction *doneAction = menu.addAction("已完成");
    QAction *deleteAction = menu.addAction("删除");
    QAction *selected = menu.exec(taskList->viewport()->mapToGlobal(pos));

    if (selected == doneAction) markTaskDone();
    else if (selected == deleteAction) deleteTask();
}

void MiniTaskPage::markTaskDone()   //标记已完成
{
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

void MiniTaskPage::deleteTask()   //选择删除
{
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

QJsonArray MiniTaskPage::getSortedTasks(const QJsonArray &array)   //将任务按照截止日期排序
{
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

QString MiniTaskPage::deadlineStatus(const QDate &date)  //将不同的任务分类
{
    int days = QDate::currentDate().daysTo(date);
    if (days == 0) return "今天截止 ⚠";
    else if (days > 0 && days <= 3) return "三天内截止";
    else if (days > 3 && days <= 7) return "一周内截止";
    return "";
}
