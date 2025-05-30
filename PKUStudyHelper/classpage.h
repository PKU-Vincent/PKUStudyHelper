#ifndef CLASSPAGE_H
#define CLASSPAGE_H

#include <QWidget>
#include "CourseInfo.h"

namespace Ui {
class ClassPage;
}

class ClassPage : public QWidget
{
    Q_OBJECT

public:
    explicit ClassPage(QWidget *parent = nullptr);
    ~ClassPage();

    void setCourseInfo(const Course& course);

private:
    Ui::ClassPage *ui;
};

#endif // CLASSPAGE_H
