QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Backend/credit_c.c \
    ../Backend/deposit_c.c \
    ../Backend/evaluation.c \
    ../Backend/parser.c \
    ../Backend/stack.c \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    calculator.cpp \
    plot.cpp \
    qcustomplot.cpp

HEADERS += \
    ../Backend/credit_c.h \
    ../Backend/data.h \
    ../Backend/deposit_c.h \
    ../Backend/rpn.h \
    ../Backend/stack.h \
    calculator.h \
    credit.h \
    deposit.h \
    plot.h \
    qcustomplot.h

FORMS += \
    calculator.ui \
    credit.ui \
    deposit.ui \
    plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
