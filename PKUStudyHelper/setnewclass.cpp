#include "setnewclass.h"
#include "ui_setnewclass.h"
#include"CourseInfo.h"

SetNewClass::SetNewClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetNewClass)
{
    ui->setupUi(this);
    connect(ui->confirm,&QPushButton::clicked,this,&SetNewClass::on_confirmButton_clicked);
    connect(ui->cancel,&QPushButton::clicked,this,&SetNewClass::on_cancelButton_clicked);
}

SetNewClass::~SetNewClass()
{
    delete ui;
}

void SetNewClass::on_confirmButton_clicked()
{
    Course course;
    course.coursename=ui->classname->text();
    course.term=ui->term->text();
    course.credit=ui->credit->text().toInt();
    course.teachername=ui->teacher->text();
    course.teachingbuilding=ui->teachingbuilding->text();
    course.classroom=ui->classroom->text();
    course.day=ui->day->text();
    course.time=ui->time->text();
    course.weeks=ui->week->text();
    course.tcontact=ui->tinfo->text();
    course.atcontact=ui->atinfo->text();
    course.tips=ui->tip->toPlainText();
    if (!course.coursename.isEmpty()) {
         emit courseCreated(course.coursename);
        this->close();
         emit newCourseCreated(course);
    }
    else{
        return;
    }
}

void SetNewClass::on_cancelButton_clicked()
{
    this->close();
}
