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
