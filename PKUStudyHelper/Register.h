#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QProgressBar>
#include <QLabel>

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
    QProgressBar *progressBar;      // 进度条控件
    QLabel *statusLabel;             // 状态标签
    void resetUI();                  // 重置UI状态
};

#endif // REGISTER_H
