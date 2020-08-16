QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_LFLAGS += -no-pie
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    ellipse.cpp \
    fontsizecombobox.cpp \
    itembutton.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    polygon.cpp \
    proptree.cpp \
    rectangle.cpp \
    polyline.cpp \
    renderarea.cpp \
    serialization.cpp \
    shape.cpp \
    shapepropdelegate.cpp \
    shapesModel.cpp \
    storage.cpp \
    text.cpp \
    line.cpp \
    textparse.cpp

HEADERS += \
    about.h \
    ellipse.h \
    fontsizecombobox.h \
    itembutton.h \
    login.h \
    mainwindow.h \
    polygon.h \
    proptree.h \
    renderarea.h \
    serialization.h \
    shapepropdelegate.h \
    shapesModel.h \
    storage.h \
    textparse.h \
    vector.h \
    rectangle.h \
    polyline.h \
    shape.h \
    text.h \
    line.h

FORMS += \
    about.ui \
    itembutton.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

DISTFILES += \
    shapes.txt
