#ifndef COURSEPAGETEMPLATE_H
#define COURSEPAGETEMPLATE_H

#include <QWidget>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QListWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>

struct Assignment {
    int id = -1;
    QString course_name;
    QString content;
    QString deadline;
    bool done = false;
};

class CoursePageTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit CoursePageTemplate(const QString& userAccount, const QString& courseName, QWidget *parent = nullptr);

    void setCourseInfo(const QString &infoText);

signals:
    void assignmentsChanged(); // 方便任务主页同步

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onAddAssignmentClicked();
    void onAssignmentContextMenuRequested(const QPoint &pos);
    void onMarkAssignmentDone();
    void onDeleteAssignment();

private:
    void loadAssignments();
    void refreshAssignmentList();
    void loadMemo();
    void saveMemo();
    void loadCourseInfo();

private:
    QString userAccount;
    QString courseName;

    QTextEdit *courseInfoEdit = nullptr;
    QTextEdit *memoEdit = nullptr;
    QListWidget *assignmentListWidget = nullptr;
    QPushButton *addAssignmentBtn = nullptr;

    QList<Assignment> assignments;

    int contextMenuCurrentAssignmentId = -1;
};

#endif // COURSEPAGETEMPLATE_H
