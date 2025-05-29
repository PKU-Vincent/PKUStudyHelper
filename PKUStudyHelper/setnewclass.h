#ifndef SETNEWCLASS_H
#define SETNEWCLASS_H

#include <QWidget>

namespace Ui {
class SetNewClass;
}

class SetNewClass : public QWidget
{
    Q_OBJECT

public:
    explicit SetNewClass(QWidget *parent = nullptr);
    ~SetNewClass();

private:
    Ui::SetNewClass *ui;
};

#endif // SETNEWCLASS_H
