QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Register.cpp \
    classpage.cpp \
    homepage.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    my_task.cpp \
    notepage_md.cpp \
    notepage_text.cpp \
    setnewclass.cpp

HEADERS += \
    CourseInfo.h \
    Register.h \
    Task.h \
    UserInfo.h \
    classpage.h \
    homepage.h \
    logindialog.h \
    mainwindow.h \
    my_task.h \
    notepage_md.h \
    notepage_text.h \
    setnewclass.h

FORMS += \
    Register.ui \
    classpage.ui \
    homepage.ui \
    logindialog.ui \
    mainwindow.ui \
    my_task.ui \
    notepage_md.ui \
    notepage_text.ui \
    setnewclass.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
