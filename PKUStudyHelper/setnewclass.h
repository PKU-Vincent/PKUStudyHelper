#ifndef SETNEWCLASS_H
#define SETNEWCLASS_H

#include <QWidget>
#include"CourseInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SetNewClass; }
QT_END_NAMESPACE

class SetNewClass : public QWidget
{
    Q_OBJECT

public:
    explicit SetNewClass(QWidget *parent = nullptr);
    ~SetNewClass();

signals:
    void courseCreated(const QString coursename);
    void newCourseCreated(const Course& course);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::SetNewClass *ui;
};

#endif // SETNEWCLASS_H
