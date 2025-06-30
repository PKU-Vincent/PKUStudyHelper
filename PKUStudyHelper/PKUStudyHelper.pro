QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MiniTaskPage.cpp \
    Register.cpp \
    TaskPage.cpp \
    classpage.cpp \
    coursepagetemplate.cpp \
    crawler.cpp \
    homepage.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    MiniTaskPage.h \
    Register.h \
    TaskPage.h \
    UserInfo.h \
    classpage.h \
    coursepagetemplate.h \
    crawler.h \
    homepage.h \
    logindialog.h \
    mainwindow.h

FORMS += \
    Register.ui \
    TaskPage.ui \
    classpage.ui \
    coursepagetemplate.ui \
    homepage.ui \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
