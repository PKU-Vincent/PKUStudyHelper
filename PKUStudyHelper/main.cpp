#include "mainwindow.h"
#include"logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDialog;
    int result=loginDialog.exec();
    if(result==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }
    else{
        return 0;
    }
}
