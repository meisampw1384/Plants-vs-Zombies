QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    change_info.cpp \
    characters.cpp \
    game_menu.cpp \
    log_in.cpp \
    main.cpp \
    menu.cpp \
    plants.cpp \
    restore_pass.cpp \
    sign_up.cpp \
    zombies.cpp

HEADERS += \
    change_info.h \
    characters.h \
    game_menu.h \
    log_in.h \
    menu.h \
    plants.h \
    restore_pass.h \
    sign_up.h \
    zombies.h

FORMS += \
    change_info.ui \
    game_menu.ui \
    log_in.ui \
    menu.ui \
    restore_pass.ui \
    sign_up.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
