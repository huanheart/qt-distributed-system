QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    func/music/musicPlayer.cpp \
    func/music/musicfunc.cpp \
    func/utils/utils.cpp \
    main.cpp \
    middleware/auth/Auth.cpp \
    request/music/hotMusic.cpp \
    request/music/musicDownload.cpp \
    request/music/musicUpload.cpp \
    request/user/captcha.cpp \
    request/user/like.cpp \
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
    widget.cpp \
    window/LoginWindow/loginwindow.cpp \
    window/Register/registerwindow.cpp \
    window/WindowManager.cpp

HEADERS += \
    func/music/musicPlayer.h \
    func/music/musicfunc.h \
    func/utils/utils.h \
    middleware/auth/Auth.h \
    request/formDataRequest.hpp \
    request/jsonRequest.hpp \
    request/music/hotMusic.h \
    request/music/musicDownload.h \
    request/music/musicUpload.h \
    request/user/captcha.h \
    request/user/like.h \
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
    widget.h \
    window/LoginWindow/loginwindow.h \
    window/Register/registerwindow.h \
    window/WindowManager.h

FORMS += \
    widget.ui \
    window/LoginWindow/loginwindow.ui \
    window/Register/registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    readme.md
