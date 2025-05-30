#include "classpage.h"
#include "ui_classpage.h"

ClassPage::ClassPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClassPage)
{
    ui->setupUi(this);
}

ClassPage::~ClassPage()
{
    delete ui;
}

void ClassPage::setCourseInfo(const Course& course)
{
    ui->classname->setText(course.coursename);
    ui->time->setText(QString("上课时间：%1%2(%3)").arg(course.day).arg(course.time).arg(course.weeks));
    ui->location->setText(QString("上课地点：%1%2").arg(course.teachingbuilding).arg(course.classroom));
    ui->tip->setPlainText(course.tips);
}
