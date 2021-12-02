
QT       += core gui printsupport network sql charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    employee.cpp \
    employee_window.cpp \
    graph.cpp \
    qcustomplot.cpp \
    databasehandler.cpp \
    filters.cpp \
    login.cpp \
    loginwin.cpp \
    main.cpp \
    mainwin.cpp \
    record.cpp \
    supervisor.cpp \
    user.cpp


HEADERS += \
    employee_window.h \
    graph.h \
    qcustomplot.h \
    databasehandler.h \
    employee.h \
    filters.h \
    login.h \
    loginwin.h \
    mainwin.h \
    qcustomplot.h \
    record.h \
    supervisor.h \
    user.h


FORMS += \
    employee_window.ui \
    loginwin.ui \
    mainwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc \
    ../URL-categorization-DFE.csv

    resource.qrc

QMAKE_CXXFLAGS += -std=gnu++11

