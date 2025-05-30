#ifndef MY_TASK_H
#define MY_TASK_H

#include <QWidget>

namespace Ui {
class my_classes;
}

class my_classes : public QWidget
{
    Q_OBJECT

public:
    explicit my_classes(QWidget *parent = nullptr);
    ~my_classes();

private:
    Ui::my_classes *ui;
};

#endif // MY_TASK_H
