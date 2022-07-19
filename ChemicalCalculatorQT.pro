QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculate.cpp \
    check_functions.cpp \
    db_worker.cpp \
    formula_parser.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    calculate.h \
    check_functions.h \
    db_worker.h \
    expression_tree.h \
    formula_parser.h \
    mainwindow.h \
    periodic_table.h \
    residue_finder.h \
    tester.h \
    tests.h

FORMS += \
    mainwindow.ui

win32:RC_ICONS += app.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
