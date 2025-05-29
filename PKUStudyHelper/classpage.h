#ifndef CLASSPAGE_H
#define CLASSPAGE_H

#include <QWidget>

namespace Ui {
class ClassPage;
}

class ClassPage : public QWidget
{
    Q_OBJECT

public:
    explicit ClassPage(QWidget *parent = nullptr);
    ~ClassPage();

private:
    Ui::ClassPage *ui;
};

#endif // CLASSPAGE_H
