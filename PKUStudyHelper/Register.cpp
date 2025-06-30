#include "Register.h"
#include "ui_Register.h"
#include "UserInfo.h"
#include "crawler.h"
#include <QDebug>
#include <QSqlError>
#include <QTimer>

extern QSqlDatabase db;

Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->yes, &QPushButton::clicked, this, &Register::on_confirmButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Register::on_cancelButton_clicked);
    ui->progressBar->setVisible(false);
    ui->statusLabel->setVisible(false);
}

Register::~Register()
{
    delete ui;
}

void Register::on_confirmButton_clicked()
{
    QString username = ui->newname->text();
    QString account = ui->newaccount->text();
    QString password = ui->newcode->text();
    QString confirmPassword = ui->confirmpassword->text();

    qDebug() << "开始注册流程：";
    qDebug() << "用户名:" << username << ", 账号:" << account << ", 密码长度:" << password.length();

    if (username.isEmpty() || account.isEmpty() || password.isEmpty()) {
        ui->message->setText("用户名、账号或密码不能为空");
        ui->message->setStyleSheet("color:red;");
        qDebug() << "注册失败：有字段为空";
        return;
    }

    if (password != confirmPassword) {
        ui->message->setText("两次输入的密码不一致");
        ui->message->setStyleSheet("color:red;");
        qDebug() << "注册失败：两次密码不一致";
        return;
    }

    // 显示进度条和状态标签
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(10);
    ui->statusLabel->setVisible(true);
    ui->statusLabel->setText("正在验证信息...");

    // 禁用按钮防止重复点击
    ui->yes->setEnabled(false);
    ui->cancelButton->setEnabled(false);

    // 使用异步方式执行注册流程，避免UI卡顿
    QTimer::singleShot(0, this, [this, username, account, password]() {
        // 1. 检查用户名是否存在
        ui->progressBar->setValue(20);
        ui->statusLabel->setText("正在验证用户名...");

        QSqlQuery query;
        query.prepare("SELECT * FROM user WHERE username = :username");
        query.bindValue(":username", username);

        if (query.exec() && query.next()) {
            ui->message->setText("该用户名已存在");
            ui->message->setStyleSheet("color:red;");
            qDebug() << "注册失败：用户名已存在";
            resetUI();
            return;
        }

        // 2. 检查账号是否存在
        ui->progressBar->setValue(40);
        ui->statusLabel->setText("正在验证账号...");

        query.prepare("SELECT * FROM user WHERE account = :account");
        query.bindValue(":account", account);

        if (query.exec() && query.next()) {
            ui->message->setText("该账号已存在");
            ui->message->setStyleSheet("color:red;");
            qDebug() << "注册失败：账号已存在";
            resetUI();
            return;
        }

        // 3. 创建用户账户
        ui->progressBar->setValue(50);
        ui->statusLabel->setText("正在创建账号...");

        query.prepare("INSERT INTO user (username, account, password) VALUES (:username, :account, :password)");
        query.bindValue(":username", username);
        query.bindValue(":account", account);
        query.bindValue(":password", password);

        if (query.exec()) {
            qDebug() << "用户信息已插入成功，准备爬取课程表";

            // 4. 爬取课程表
            ui->progressBar->setValue(60);
            ui->statusLabel->setText("正在获取课程表...");

            QMap<int, QMap<int, QString>> schedule = fetchSchedule(account, password);

            // 5. 保存课程表数据
            ui->progressBar->setValue(70);
            ui->statusLabel->setText("正在保存课程信息...");

            qDebug() << "获取到的课程表如下：";
            int totalCourses = 0;
            int processedCourses = 0;

            // 计算总课程数用于进度计算
            for (auto dayIt = schedule.begin(); dayIt != schedule.end(); ++dayIt) {
                totalCourses += dayIt.value().size();
            }

            for (auto dayIt = schedule.begin(); dayIt != schedule.end(); ++dayIt) {
                int weekday = dayIt.key();
                const QMap<int, QString> &dayCourses = dayIt.value();

                for (auto periodIt = dayCourses.begin(); periodIt != dayCourses.end(); ++periodIt) {
                    int period = periodIt.key();
                    QString rawCourseInfo = periodIt.value();

                    if (rawCourseInfo.trimmed().isEmpty()) {
                        qDebug() << "跳过空课程: Weekday:" << weekday << " Period:" << period;
                        continue;
                    }

                    qDebug() << "Weekday:" << weekday << "Period:" << period << "Course:" << rawCourseInfo;

                    ParsedCourseInfo info = parseCourseInfo(rawCourseInfo);

                    QSqlQuery insertQuery;
                    insertQuery.prepare("INSERT INTO courses (account, weekday, period, course_name, classroom, teacher, remark, exam_info) "
                                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
                    insertQuery.addBindValue(account);
                    insertQuery.addBindValue(weekday);
                    insertQuery.addBindValue(period);
                    insertQuery.addBindValue(info.name);
                    insertQuery.addBindValue(info.classroom);
                    insertQuery.addBindValue(info.teacher);
                    insertQuery.addBindValue(info.remark);
                    insertQuery.addBindValue(info.exam_info);

                    if (!insertQuery.exec()) {
                        qDebug() << "插入课程失败：" << insertQuery.lastError().text();
                    } else {
                        qDebug() << "成功插入课程：" << info.name;
                    }

                    // 更新进度条
                    processedCourses++;
                    int progress = 70 + (processedCourses * 20) / qMax(1, totalCourses); // 70-90%
                    ui->progressBar->setValue(progress);
                }
            }

            // 6. 验证插入结果
            ui->progressBar->setValue(90);
            ui->statusLabel->setText("正在完成设置...");

            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT * FROM courses WHERE account = :acc");
            checkQuery.bindValue(":acc", account);

            if (checkQuery.exec()) {
                while (checkQuery.next()) {
                    QString acc = checkQuery.value("account").toString();
                    int weekday = checkQuery.value("weekday").toInt();
                    int period = checkQuery.value("period").toInt();
                    QString cname = checkQuery.value("course_name").toString();
                    qDebug() << "[数据库记录]" << acc << weekday << period << cname;
                }
            } else {
                qDebug() << "检查插入课程时失败：" << checkQuery.lastError().text();
            }

            // 7. 完成注册
            ui->progressBar->setValue(100);
            ui->statusLabel->setText("注册完成！正在准备登录...");

            // 延迟1秒后关闭对话框，让用户看到完成状态
            QTimer::singleShot(1000, this, [this]() {
                emit registerSuccess();
                accept();
            });
        } else {
            qDebug() << "注册失败，错误信息：" << query.lastError().text();
            ui->message->setText("注册失败，请稍后再试");
            ui->message->setStyleSheet("color:red;");
            resetUI();
        }
    });
}

// 重置UI状态
void Register::resetUI()
{
    ui->progressBar->setVisible(false);
    ui->statusLabel->setVisible(false);
    ui->yes->setEnabled(true);
    ui->cancelButton->setEnabled(true);
}

void Register::on_cancelButton_clicked()
{
    emit registerCancel();
    this->close();
}
