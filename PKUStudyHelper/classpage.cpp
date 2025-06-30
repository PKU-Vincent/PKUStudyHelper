#include "classpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMenu>
#include <QInputDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QPalette>
#include <QPixmap>

ClassPage::ClassPage(const QString& account, QWidget *parent) : QWidget(parent), userAccount(account)
{
    // ===== 设置背景图 =====
    QPalette pal = this->palette();
    QPixmap bgPixmap(":/new/prefix1/纸质背景.jpg");
    if (!bgPixmap.isNull()) {
        bgPixmap = bgPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        pal.setBrush(QPalette::Window, QBrush(bgPixmap));
        this->setPalette(pal);
        this->setAutoFillBackground(true);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // ====== 上方：课程表区域 ======
    QLabel *courseLabel = new QLabel("课程表");
    courseLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #333333;");
    mainLayout->addWidget(courseLabel);

    courseTable = new QTableWidget(this);
    courseTable->setRowCount(11);
    courseTable->setColumnCount(7);
    QStringList headers;
    for (int i = 1; i <= 7; ++i) headers << weekdayToString(i);
    courseTable->setHorizontalHeaderLabels(headers);
    QStringList rowHeaders;
    for (int i = 1; i <= 11; ++i) rowHeaders << QString("%1节").arg(i);
    courseTable->setVerticalHeaderLabels(rowHeaders);
    courseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    courseTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    courseTable->setStyleSheet(R"(
        QTableWidget {
            background-color: rgba(255, 255, 255, 0.8);
            font-size: 14px;
            font-family: 'Microsoft YaHei';
            border-radius: 8px;
        }
        QHeaderView::section {
            background-color: #f0f0f0;
            font-weight: bold;
        }
    )");
    mainLayout->addWidget(courseTable, 1);

    // ====== 下方：考试时间轴标签和添加按钮 ======
    QHBoxLayout *examTopLayout = new QHBoxLayout();
    QLabel *examLabel = new QLabel("考试时间轴");
    examLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #333333;");

    addExamBtn = new QPushButton("添加考试");
    addExamBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            padding: 6px 12px;
            border: none;
            border-radius: 6px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    examTopLayout->addWidget(examLabel);
    examTopLayout->addStretch();
    examTopLayout->addWidget(addExamBtn);
    mainLayout->addLayout(examTopLayout);

    // 考试卡片列表
    examListWidget = new QListWidget(this);
    examListWidget->setFlow(QListView::LeftToRight);
    examListWidget->setResizeMode(QListView::Adjust);
    examListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    examListWidget->setSpacing(10);
    examListWidget->setStyleSheet(R"(
        QListWidget {
            background-color: transparent;
        }
    )");
    mainLayout->addWidget(examListWidget, 1);

    connect(addExamBtn, &QPushButton::clicked, this, &ClassPage::onAddExamClicked);
    connect(examListWidget, &QListWidget::customContextMenuRequested, this, &ClassPage::onExamItemContextMenuRequested);

    loadCourseTable();
    loadExamList();
}


QString ClassPage::weekdayToString(int weekday)
{
    static const QStringList weekNames = { "周一", "周二", "周三", "周四", "周五", "周六", "周日" };
    return weekNames.value(weekday - 1, "未知");
}

void ClassPage::loadCourseTable() //加载课表
{
    courseTable->clearContents();
    QSqlQuery query;
    query.prepare("SELECT weekday, period, course_name, classroom FROM courses WHERE account = :account");
    query.bindValue(":account", userAccount);
    if (!query.exec()) {
        qDebug() << "加载课程表失败：" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int weekday = query.value(0).toInt();
        int period = query.value(1).toInt();
        QString courseName = query.value(2).toString();
        QString classroom = query.value(3).toString();

        if (weekday == 0) weekday = 7;
        int col = weekday - 1;
        int row = period - 1;

        QString text = QString("%1 (%2)").arg(courseName, classroom);
        QTableWidgetItem *item = new QTableWidgetItem(text);
        item->setTextAlignment(Qt::AlignCenter);
        courseTable->setItem(row, col, item);
    }                                               //从courses表中获取信息

    mergeCourseCells();
}

void ClassPage::mergeCourseCells()   //合并单元格
{
    for (int col = 0; col < courseTable->columnCount(); ++col) {
        int startRow = 0;
        while (startRow < courseTable->rowCount()) {
            QTableWidgetItem *startItem = courseTable->item(startRow, col);
            if (!startItem || startItem->text().isEmpty()) {
                ++startRow;
                continue;
            }

            QString text = startItem->text();
            int count = 1;
            for (int r = startRow + 1; r < courseTable->rowCount(); ++r) {
                QTableWidgetItem *item = courseTable->item(r, col);
                if (item && item->text() == text) {
                    ++count;
                } else {
                    break;
                }
            }

            if (count > 1) {
                courseTable->setSpan(startRow, col, count, 1);
                for (int r = startRow + 1; r < startRow + count; ++r)
                    courseTable->setItem(r, col, new QTableWidgetItem(""));
            }

            startRow += count;
        }
    }
}

void ClassPage::loadExamList()   //加载考试时间轴
{
    examListWidget->clear();

    QSqlQuery query;
    query.prepare("SELECT id, course_name, exam_date, start_time, end_time, location "
                  "FROM exams WHERE account = :account ORDER BY exam_date ASC, start_time ASC"); //从考试表中加载信息
    query.bindValue(":account", userAccount);
    if (!query.exec()) {
        qDebug() << "加载考试失败：" << query.lastError().text();
        return;
    }

    QDate today = QDate::currentDate();

    while (query.next()) {
        int id = query.value(0).toInt();
        QString course = query.value(1).toString();
        QString dateStr = query.value(2).toString();
        QString start = query.value(3).toString();
        QString end = query.value(4).toString();
        QString location = query.value(5).toString();

        QString timeStr = QString("%1 %2 ~ %3").arg(dateStr, start, end);

        QWidget *card = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(card);
        QLabel *label1 = new QLabel(course);
        QLabel *label2 = new QLabel(timeStr);
        QLabel *label3 = new QLabel(location);
        layout->addWidget(label1);
        layout->addWidget(label2);
        layout->addWidget(label3);
        card->setLayout(layout);
        card->setMinimumWidth(180);

        QDate examDate = QDate::fromString(dateStr, "yyyy-MM-dd");
        if (examDate == today) {
            card->setStyleSheet("background-color: #ffe6e6; border: 2px solid red; border-radius: 10px; padding: 8px;");
        } else {
            card->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 10px; padding: 8px;");
        }

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(card->sizeHint());
        item->setData(Qt::UserRole, id);
        examListWidget->addItem(item);
        examListWidget->setItemWidget(item, card);
    }
}

void ClassPage::onAddExamClicked()
{
    showAddExamDialog();
}

void ClassPage::showAddExamDialog()  //设计添加考试的窗口
{
    QDialog dialog(this);
    dialog.setWindowTitle("添加考试");
    QFormLayout form(&dialog);

    QComboBox *courseCombo = new QComboBox(&dialog);
    QSqlQuery query;
    query.prepare("SELECT DISTINCT course_name FROM courses WHERE account = :account");
    query.bindValue(":account", userAccount);
    if (query.exec()) {
        while (query.next())
            courseCombo->addItem(query.value(0).toString());
    }
    form.addRow("课程", courseCombo);

    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    dateEdit->setCalendarPopup(true);
    form.addRow("考试日期", dateEdit);

    QTimeEdit *startEdit = new QTimeEdit(QTime(8, 0), &dialog);
    QTimeEdit *endEdit = new QTimeEdit(QTime(10, 0), &dialog);
    startEdit->setDisplayFormat("HH:mm");
    endEdit->setDisplayFormat("HH:mm");
    form.addRow("开始时间", startEdit);
    form.addRow("结束时间", endEdit);

    QHBoxLayout *locLayout = new QHBoxLayout;
    QComboBox *building = new QComboBox(&dialog);
    building->addItems({"一教", "二教", "三教", "四教", "理教", "文史", "地学"});
    QLineEdit *room = new QLineEdit(&dialog);
    room->setPlaceholderText("教室号");
    locLayout->addWidget(building);
    locLayout->addWidget(room);
    QWidget *locWidget = new QWidget(&dialog);
    locWidget->setLayout(locLayout);
    form.addRow("地点", locWidget);

    QDialogButtonBox box(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form.addRow(&box);
    connect(&box, &QDialogButtonBox::accepted, [&]() {
        if (courseCombo->currentText().isEmpty() || room->text().trimmed().isEmpty() || startEdit->time() >= endEdit->time())
            return;
        dialog.accept();
    });
    connect(&box, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString loc = building->currentText() + room->text().trimmed();
        QSqlQuery insert;
        insert.prepare("INSERT INTO exams (account, course_name, exam_date, start_time, end_time, location) "  //尝试将考试信息插入考试表中储存起来
                       "VALUES (:account, :course, :date, :start, :end, :loc)");
        insert.bindValue(":account", userAccount);
        insert.bindValue(":course", courseCombo->currentText());
        insert.bindValue(":date", dateEdit->date().toString("yyyy-MM-dd"));
        insert.bindValue(":start", startEdit->time().toString("HH:mm"));
        insert.bindValue(":end", endEdit->time().toString("HH:mm"));
        insert.bindValue(":loc", loc);
        if (!insert.exec()) {
            QMessageBox::critical(this, "错误", "添加考试失败:\n" + insert.lastError().text());
            return;
        }
        loadExamList();
    }
}

void ClassPage::onExamItemContextMenuRequested(const QPoint &pos)  //删除考试
{
    QListWidgetItem *item = examListWidget->itemAt(pos);
    if (!item) return;

    QMenu menu;
    QAction *del = menu.addAction("删除考试");
    if (menu.exec(examListWidget->viewport()->mapToGlobal(pos)) == del) {
        int id = item->data(Qt::UserRole).toInt();
        QSqlQuery query;
        query.prepare("DELETE FROM exams WHERE id = :id");
        query.bindValue(":id", id);
        if (!query.exec()) {
            QMessageBox::critical(this, "错误", "删除失败:\n" + query.lastError().text());
            return;
        }
        loadExamList();
    }
}
