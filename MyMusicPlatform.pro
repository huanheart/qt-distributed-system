QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    func/music/musicPlayer.cpp \
    main.cpp \
    middleware/auth/Auth.cpp \
    request/music/musicDownload.cpp \
    request/music/musicUpload.cpp \
    request/user/captcha.cpp \
    request/user/login.cpp \
    request/user/register.cpp \
    requestSender/formdatarequestsender.cpp \
    requestSender/jsonRequestSender.cpp \
    requestSender/musicrequestsender.cpp \
    requestSender/userrequestsender.cpp \
    response/jsonResponse.cpp \
    router/musicRouter.cpp \
    router/router.cpp \
    router/userRouter.cpp \
    widget.cpp

HEADERS += \
    func/music/musicPlayer.h \
    middleware/auth/Auth.h \
    request/formDataRequest.hpp \
    request/jsonRequest.hpp \
    request/music/musicDownload.h \
    request/music/musicUpload.h \
    request/user/captcha.h \
    request/user/login.h \
    request/user/login.hpp \
    request/user/register.h \
    request/user/register.hpp \
    requestSender/formdatarequestsender.h \
    requestSender/jsonRequestSender.h \
    requestSender/musicrequestsender.h \
    requestSender/userrequestsender.h \
    response/jsonResponse.h \
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
