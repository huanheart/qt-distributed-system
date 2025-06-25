QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    request/music/musicDownload.cpp \
    request/music/musicUpload.cpp \
    request/user/captcha.cpp \
    request/user/login.cpp \
    request/user/register.cpp \
    requestSender/jsonRequestSender.cpp \
    requestSender/userrequestsender.cpp \
    router/musicRouter.cpp \
    router/router.cpp \
    router/userRouter.cpp \
    widget.cpp

HEADERS += \
    request/jsonRequest.hpp \
    request/music/musicDownload.h \
    request/music/musicUpload.h \
    request/user/captcha.h \
    request/user/login.h \
    request/user/login.hpp \
    request/user/register.h \
    request/user/register.hpp \
    requestSender/jsonRequestSender.h \
    requestSender/userrequestsender.h \
    router/musicRouter.h \
    router/router.h \
    router/userRouter.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    readme.md
