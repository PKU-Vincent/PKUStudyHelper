#include "notepage_text.h"
#include "ui_notepage_text.h"

NotePage::NotePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotePage)
{
    ui->setupUi(this);
}

NotePage::~NotePage()
{
    delete ui;
}
