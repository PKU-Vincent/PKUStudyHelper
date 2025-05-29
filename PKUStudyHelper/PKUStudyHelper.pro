QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classpage.cpp \
    homepage.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    notepage_md.cpp \
    notepage_text.cpp \
    register.cpp \
    setnewclass.cpp

HEADERS += \
    CourseInfo.h \
    Task.h \
    UserInfo.h \
    classpage.h \
    homepage.h \
    logindialog.h \
    mainwindow.h \
    notepage_md.h \
    notepage_text.h \
    register.h \
    setnewclass.h

FORMS += \
    classpage.ui \
    homepage.ui \
    logindialog.ui \
    mainwindow.ui \
    notepage_md.ui \
    notepage_text.ui \
    register.ui \
    setnewclass.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
