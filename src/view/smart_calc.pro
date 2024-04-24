QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS = -Wall -Werror -Wextra

SOURCES += \
    ../model/calculation.cc \
    ../model/token.cc \
    ../controller/controller.cc \
    ../model/model.cc \
    ../model/graph.cc\
    ../model/date.cc \
    ../model/deposit.cc \
    ../model/credit.cc \
    drawgraph.cc \
    ../main.cc \
    mainwindow.cc

HEADERS += \
    ../model/calculation.h \
    ../model/token.h \
    ../controller/controller.h \
    ../model/model.h \
    ../model/graph.h \
    ../model/date.h \
    ../model/deposit.h \
    ../model/credit.h \
    drawgraph.h \
    mainwindow.h

FORMS += \
    drawgraph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
