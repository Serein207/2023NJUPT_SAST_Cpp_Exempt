QT       += core gui widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithms.cpp \
    cell.cpp \
    main.cpp \
    board.cpp \
    mainui.cpp \
    piece.cpp

HEADERS += \
    algorithms.h \
    bing_zu.h \
    board.h \
    cell.h \
    global.h \
    jiang_shuai.h \
    ju.h \
    ma.h \
    mainui.h \
    pao.h \
    piece.h \
    shi.h \
    xiang.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
