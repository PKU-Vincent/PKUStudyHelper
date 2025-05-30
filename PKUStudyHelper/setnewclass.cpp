#include "setnewclass.h"
#include "ui_setnewclass.h"

SetNewClass::SetNewClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetNewClass)
{
    ui->setupUi(this);
}

SetNewClass::~SetNewClass()
{
    delete ui;
}

void SetNewClass::on_confirmButton_clicked()
{
    QString courseName = ui->classname->text();
    if (!courseName.isEmpty()) {
        emit courseCreated(courseName);
    }
}
