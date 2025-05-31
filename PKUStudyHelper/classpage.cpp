#include "classpage.h"
#include "ui_classpage.h"
#include <QCoreApplication>
#include <QString>
#include <QRegularExpression>
#include <QDebug>

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

void ClassPage::setCourseInfo(const QVector<CourseInfo>& course)
{
    bool name_shown=false;
    bool tips_shown=false;
    bool classroom_shown=false;
    bool parity_shown=false;
    QString classroom;
    QString parity;
    QString time="";
    for(const CourseInfo& it:course)
    {
        if(!name_shown)
        {
            ui->classname->setText(it.name);
            name_shown=true;
        }
        if(!tips_shown)
        {
            ui->tip->setPlainText(it.detail);
            tips_shown=true;
        }
        if(!classroom_shown)
        {
            QRegularExpression re("([\\u4e00-\\u9fa5]+\\d+)");
            QRegularExpressionMatch match = re.match(it.detail);
            if (match.hasMatch()) {
                QString classroom = match.captured(0);
                qDebug() << classroom;
            }
            ui->classroom->setText(classroom);
            classroom_shown=true;
        }
        if(!parity_shown)
        {
            QRegularExpression re("(单周|双周|每周)");
            QRegularExpressionMatch match = re.match(it.detail);
            if (match.hasMatch()) {
                parity = match.captured(0);
                qDebug() << parity;
            }
            ui->parity->setText(parity);
        }
        time+=it.weekday+" "+it.periods.join(",")+"\n";
    }
    ui->time->setText(time);
}
