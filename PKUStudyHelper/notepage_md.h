#ifndef NOTEPAGE_MD_H
#define NOTEPAGE_MD_H

#include <QWidget>

namespace Ui {
class notepage_md;
}

class notepage_md : public QWidget
{
    Q_OBJECT

public:
    explicit notepage_md(QWidget *parent = nullptr);
    ~notepage_md();

private:
    Ui::notepage_md *ui;
};

#endif // NOTEPAGE_MD_H
