#ifndef NOTEPAGE_TEXT_H
#define NOTEPAGE_TEXT_H

#include <QWidget>

namespace Ui {
class NotePage;
}

class NotePage : public QWidget
{
    Q_OBJECT

public:
    explicit NotePage(QWidget *parent = nullptr);
    ~NotePage();

private:
    Ui::NotePage *ui;
};

#endif // NOTEPAGE_TEXT_H
