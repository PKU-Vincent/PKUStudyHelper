#include "notepage_md.h"
#include "ui_notepage_md.h"

notepage_md::notepage_md(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::notepage_md)
{
    ui->setupUi(this);
}

notepage_md::~notepage_md()
{
    delete ui;
}
