#include "coursepagetemplate.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QEvent>
#include <QCalendarWidget>
#include <QDialog>
#include <QFormLayout>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QPalette>
#include <QPixmap>

CoursePageTemplate::CoursePageTemplate(const QString& userAccount, const QString& courseName, QWidget *parent)
    : QWidget(parent), userAccount(userAccount), courseName(courseName)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 设置背景
    QPalette globalPalette = this->palette();
    QPixmap bgPixmap(":/new/prefix1/纸质背景.jpg");
    if (!bgPixmap.isNull()) {
        bgPixmap = bgPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        globalPalette.setBrush(QPalette::Window, QBrush(bgPixmap));
        this->setPalette(globalPalette);
        this->setAutoFillBackground(true);
    }

    QLabel *titleLabel = new QLabel(courseName, this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    mainLayout->addLayout(middleLayout);

    courseInfoEdit = new QTextEdit(this);
    courseInfoEdit->setReadOnly(true);
    courseInfoEdit->setPlaceholderText("课程信息");
    courseInfoEdit->setFixedHeight(120);
    courseInfoEdit->setStyleSheet(R"(
        QTextEdit {
            font-size: 16px;
            background-color: rgba(255, 255, 255, 0.8);
            border: 1px solid #ccc;
            border-radius: 10px;
            padding: 10px;
        })");
    middleLayout->addWidget(courseInfoEdit, 1);

    memoEdit = new QTextEdit(this);
    memoEdit->setPlaceholderText("备忘录");
    memoEdit->setFixedHeight(120);
    memoEdit->setStyleSheet(R"(
        QTextEdit {
            font-size: 14px;
            background-color: rgba(255, 255, 255, 0.8);
            border: 1px solid #ccc;
            border-radius: 10px;
            padding: 10px;
        })");
    memoEdit->installEventFilter(this);
    middleLayout->addWidget(memoEdit, 1);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    mainLayout->addLayout(bottomLayout);

    addAssignmentBtn = new QPushButton("添加作业", this);
    addAssignmentBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 8px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #45a049;
        })");
    bottomLayout->addWidget(addAssignmentBtn);

    assignmentListWidget = new QListWidget(this);
    assignmentListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    assignmentListWidget->setStyleSheet(R"(
        QListWidget {
            background-color: rgba(255, 255, 255, 0.8);
            border-radius: 8px;
            font-size: 14px;
        })");
    bottomLayout->addWidget(assignmentListWidget, 1);

    connect(addAssignmentBtn, &QPushButton::clicked, this, &CoursePageTemplate::onAddAssignmentClicked);
    connect(assignmentListWidget, &QListWidget::customContextMenuRequested,
            this, &CoursePageTemplate::onAssignmentContextMenuRequested);

    loadCourseInfo();
    loadAssignments();
    loadMemo();
}

void CoursePageTemplate::loadCourseInfo() {
    qDebug() << "加载课程信息：" << userAccount << courseName;

    QSqlQuery query;
    query.prepare("SELECT teacher, remark, exam_info FROM courses WHERE account = :account AND course_name = :course_name LIMIT 1");
    query.bindValue(":account", userAccount);
    query.bindValue(":course_name", courseName.trimmed());

    if (!query.exec()) {
        qDebug() << "查询失败：" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString info = QString("教师：%1\n备注：%2\n考试信息：%3")
                           .arg(query.value(0).toString())
                           .arg(query.value(1).toString())
                           .arg(query.value(2).toString());
        courseInfoEdit->setPlainText(info);
    } else {
        qDebug() << "没有查到对应课程信息！";
    }
}
void CoursePageTemplate::loadAssignments() {
    assignments.clear();
    QSqlQuery query;
    query.prepare("SELECT id, content, deadline, done FROM assignments WHERE account = :account AND course_name = :course_name");
    query.bindValue(":account", userAccount);
    query.bindValue(":course_name", courseName);
    if (query.exec()) {
        while (query.next()) {
            Assignment a;
            a.id = query.value(0).toInt();
            a.course_name = courseName;
            a.content = query.value(1).toString();
            a.deadline = query.value(2).toString();
            a.done = query.value(3).toBool();
            assignments.append(a);
        }
    }
    refreshAssignmentList();
}

void CoursePageTemplate::loadMemo() {
    QSqlQuery query;
    query.prepare("SELECT course_memo FROM user WHERE account = :account");
    query.bindValue(":account", userAccount);
    if (query.exec() && query.next()) {
        memoEdit->setPlainText(query.value(0).toString());
    }
}

void CoursePageTemplate::refreshAssignmentList() {
    assignmentListWidget->clear();
    std::sort(assignments.begin(), assignments.end(), [](const Assignment &a, const Assignment &b) {
        return a.deadline < b.deadline;
    });
    for (const Assignment &a : assignments) {
        QListWidgetItem *item = new QListWidgetItem(a.content + " (截止: " + a.deadline + ")");
        if (a.done) {
            item->setForeground(Qt::gray);
            item->setFont(QFont("", -1, QFont::Normal, true));
        }
        item->setData(Qt::UserRole, a.id);
        assignmentListWidget->addItem(item);
    }
}

void CoursePageTemplate::onAssignmentContextMenuRequested(const QPoint &pos) {
    QListWidgetItem *item = assignmentListWidget->itemAt(pos);
    if (!item) return;
    QMenu menu(this);
    menu.addAction("标记完成", this, &CoursePageTemplate::onMarkAssignmentDone);
    menu.addAction("删除作业", this, &CoursePageTemplate::onDeleteAssignment);
    menu.exec(assignmentListWidget->mapToGlobal(pos));
}

void CoursePageTemplate::onMarkAssignmentDone() {
    QListWidgetItem *item = assignmentListWidget->currentItem();
    if (!item) return;
    int id = item->data(Qt::UserRole).toInt();
    for (Assignment &a : assignments) {
        if (a.id == id) {
            a.done = true;
            QSqlQuery query;
            query.prepare("UPDATE assignments SET done = 1 WHERE id = :id");
            query.bindValue(":id", id);
            query.exec();
            break;
        }
    }
    refreshAssignmentList();
    emit assignmentsChanged();
}

void CoursePageTemplate::onDeleteAssignment() {
    QListWidgetItem *item = assignmentListWidget->currentItem();
    if (!item) return;
    int id = item->data(Qt::UserRole).toInt();
    for (int i = 0; i < assignments.size(); ++i) {
        if (assignments[i].id == id) {
            assignments.remove(i);
            QSqlQuery query;
            query.prepare("DELETE FROM assignments WHERE id = :id");
            query.bindValue(":id", id);
            query.exec();
            break;
        }
    }
    refreshAssignmentList();
    emit assignmentsChanged();
}

bool CoursePageTemplate::eventFilter(QObject *obj, QEvent *event) {
    if (obj == memoEdit && event->type() == QEvent::FocusOut) {
        saveMemo();
    }
    return QWidget::eventFilter(obj, event);
}

void CoursePageTemplate::saveMemo() {
    QString memoText = memoEdit->toPlainText();
    QSqlQuery query;
    query.prepare("UPDATE user SET course_memo = :memo WHERE account = :account");
    query.bindValue(":memo", memoText);
    query.bindValue(":account", userAccount);
    query.exec();
}

void CoursePageTemplate::onAddAssignmentClicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("添加作业");
    QFormLayout *formLayout = new QFormLayout(&dialog);

    QLineEdit *contentEdit = new QLineEdit(&dialog);
    QDateEdit *deadlineEdit = new QDateEdit(QDate::currentDate(), &dialog);
    deadlineEdit->setCalendarPopup(true);
    deadlineEdit->setDisplayFormat("yyyy-MM-dd");

    formLayout->addRow("作业内容：", contentEdit);
    formLayout->addRow("截止日期：", deadlineEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString content = contentEdit->text().trimmed();
        QString deadline = deadlineEdit->date().toString("yyyy-MM-dd");
        if (content.isEmpty()) return;

        QSqlQuery query;
        query.prepare("INSERT INTO assignments (account, course_name, content, deadline, done) VALUES (:account, :course_name, :content, :deadline, 0)");
        query.bindValue(":account", userAccount);
        query.bindValue(":course_name", courseName);
        query.bindValue(":content", content);
        query.bindValue(":deadline", deadline);
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "添加作业失败:\n" + query.lastError().text());
            return;
        }
        int newId = query.lastInsertId().toInt();

        Assignment a;
        a.id = newId;
        a.course_name = courseName;
        a.content = content;
        a.deadline = deadline;
        a.done = false;
        assignments.append(a);

        QSqlQuery userQuery;
        userQuery.prepare("SELECT json_tasks_content FROM user WHERE account = :account");
        userQuery.bindValue(":account", userAccount);
        userQuery.exec();

        QJsonArray tasksArray;
        if (userQuery.next()) {
            QString jsonStr = userQuery.value(0).toString();
            if (!jsonStr.isEmpty()) {
                QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
                if (doc.isArray()) tasksArray = doc.array();
            }
        }

        QJsonObject newTask;
        newTask["deadline"] = deadline;
        newTask["name"] = courseName + " 作业：" + content;
        newTask["done"] = false;
        tasksArray.append(newTask);

        QSqlQuery updateUser;
        updateUser.prepare("UPDATE user SET json_tasks_content = :json WHERE account = :account");
        updateUser.bindValue(":json", QString(QJsonDocument(tasksArray).toJson(QJsonDocument::Compact)));
        updateUser.bindValue(":account", userAccount);
        if (!updateUser.exec()) {
            qDebug() << "同步写入任务失败:" << updateUser.lastError().text();
        }

        refreshAssignmentList();
        emit assignmentsChanged();
    }
}
