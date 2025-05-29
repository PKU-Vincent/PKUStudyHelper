#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include"ui_register.h"


namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

signals:
    void registerSuccess();
    void registerCancel();

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
