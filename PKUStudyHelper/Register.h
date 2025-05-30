#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include"ui_Register.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>

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
    QSqlDatabase db;
    void openDatabase();
};

#endif // REGISTER_H
