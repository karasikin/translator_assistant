QT += core gui widgets

CONFIG += c++17

LIBS += -pthread -lrt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = translator/ blocker/

SOURCES += \
        clipboard.cpp \
        main.cpp \
        translator/translatortrshell.cpp \
        blocker/blocker.cpp \
        window.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    clipboard.h \
    main.h \
    translator/i_translator.h \
    translator/translatortrshell.h \
    blocker/blocker.h \
    window.h
