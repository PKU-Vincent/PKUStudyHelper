#ifndef CLASSPAGE_H
#define CLASSPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include<QHBoxLayout>

class ClassPage : public QWidget
{
    Q_OBJECT
public:
    explicit ClassPage(const QString& account, QWidget *parent = nullptr);

private:
    QString userAccount;

    QTableWidget *courseTable;
    QListWidget *examListWidget;
    QPushButton *addExamBtn;

    // 把数字星期转为字符串，如周一、周二等
    QString weekdayToString(int weekday);

    // 载入课程表，填充QTableWidget
    void loadCourseTable();

    // 合并课程表中相邻相同课程的单元格
    void mergeCourseCells();

    // 载入考试时间轴列表
    void loadExamList();

    QHBoxLayout *examLayout;

    void setupExamSection();

private slots:
    // 点击添加考试按钮
    void onAddExamClicked();

    // 右键考试列表弹菜单
    void onExamItemContextMenuRequested(const QPoint &pos);

private:
    // 弹出添加考试对话框
    void showAddExamDialog();
};

#endif // CLASSPAGE_H
