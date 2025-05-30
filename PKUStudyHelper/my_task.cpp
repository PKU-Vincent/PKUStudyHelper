#include "my_task.h"
#include "ui_my_task.h"

my_classes::my_classes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::my_classes)
{
    ui->setupUi(this);
}

my_classes::~my_classes()
{
    delete ui;
}
