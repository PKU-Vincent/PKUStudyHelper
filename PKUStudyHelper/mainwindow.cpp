#include "mainwindow.h"
#include "HomePage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QMenu>
#include<QList>
#include <QAction>
#include<QWidget>
#include "Task.h"
#include"classpage.h"
#include"UserInfo.h"
#include"CourseInfo.h"

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
    navList->addItem("我的主页");
    navList->addItem("我的任务");
    navList->addItem("我的课程");

    navLayout->addWidget(navList);
    navLayout->addStretch();
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
    stackedWidget->addWidget(homePage); // index 0

    // 创建其他页面
    QWidget *taskPage = new QWidget(this);
    QLabel *taskLabel = new QLabel("这是任务主页", taskPage);
    QVBoxLayout *taskLayout = new QVBoxLayout(taskPage);
    taskLayout->addWidget(taskLabel);
    stackedWidget->addWidget(taskPage); // index 1

    QJsonObject scheduleData=getScheduleFromPython(current_user.account,current_user.password);
    if (scheduleData.contains("error")) {
        qDebug() << "Login failed:" << scheduleData["error"].toString();
        // 显示错误信息给用户
    } else {
        qDebug() << "Schedule data received:" << scheduleData;
    }
    QVector<QMap<QString, QString>> scheduleEntries = jsonObjectToScheduleEntries(scheduleData);
    ParsedScheduleResult result = parseAndCategorizeSchedule(scheduleEntries);
    int number=result.name_index.size();
    QList<QWidget*> coursewidgets;
    for(int i=0;i<number;++i)
    {
        ClassPage* w=new ClassPage(this);
        coursewidgets.append(w);
        w->setCourseInfo(result.name_index[result.name_list[i]]);
        stackedWidget->addWidget(w);//index i+2
    }

    mainLayout->addWidget(navWidget);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setStretch(0, 0);
    mainLayout->setStretch(1, 1);
    setCentralWidget(central);
    navList->setCurrentRow(0);

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

QJsonObject MainWindow::getScheduleFromPython(const QString& studentId, const QString& password) {
    QProcess process;
    QString pythonExecutable = "python";  // 需确保 Python 已安装并在系统路径中
    QString scriptPath = "pku_portal.py"; // Python 脚本路径

    // 设置命令行参数
    QStringList arguments;
    arguments << scriptPath << studentId << password;

    // 启动进程
    process.start(pythonExecutable, arguments);
    if (!process.waitForStarted()) {
        qDebug() << "Error: Failed to start Python process:" << process.errorString();
        return QJsonObject({{"error", "Failed to start Python process"}});
    }

    // 等待进程完成
    if (!process.waitForFinished()) {
        qDebug() << "Error: Python process timed out:" << process.errorString();
        return QJsonObject({{"error", "Python process timed out"}});
    }

    // 获取标准输出和错误输出
    QByteArray stdoutData = process.readAllStandardOutput();
    QByteArray stderrData = process.readAllStandardError();

    // 检查错误输出
    if (!stderrData.isEmpty()) {
        qDebug() << "Python error:" << QString::fromUtf8(stderrData);
    }

    // 解析 JSON 数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(stdoutData);
    if (jsonDoc.isNull()) {
        qDebug() << "Error: Failed to parse JSON:" << QString::fromUtf8(stdoutData);
        return QJsonObject({{"error", "Failed to parse JSON"}});
    }

    return jsonDoc.object();
}
QVector<QMap<QString, QString>> MainWindow:: jsonObjectToScheduleEntries(const QJsonObject& jsonObj) {
    QVector<QMap<QString, QString>> entries;

    // 假设 JSON 数据是一个数组（例如 "course" 键对应数组）
    if (jsonObj.contains("course") && jsonObj["course"].isArray()) {
        QJsonArray courseArray = jsonObj["course"].toArray();

        for (const QJsonValue& val : courseArray) {
            if (val.isObject()) {
                QJsonObject obj = val.toObject();
                QMap<QString, QString> entry;

                // 遍历 JSON 对象的键值对，假设键为 "mon", "tue" 等星期代码或其他字段
                for (const QString& key : obj.keys()) {
                    if (obj[key].isString()) {
                        entry[key] = obj[key].toString();
                    } else if (obj[key].isObject()) {
                        // 处理嵌套对象（如有需要）
                        QJsonObject subObj = obj[key].toObject();
                        for (const QString& subKey : subObj.keys()) {
                            entry[subKey] = subObj[subKey].toString();
                        }
                    }
                }
                entries.append(entry);
            }
        }
    }
    return entries;
}
