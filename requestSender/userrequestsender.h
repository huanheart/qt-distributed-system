#ifndef USERREQUESTSENDER_H
#define USERREQUESTSENDER_H

#include <QObject>
#include<QMessageBox>

#include"request/user/captcha.h"
#include"request/user/login.h"
#include"request/user/register.h"

#include"../response/jsonResponse.h"

#include"jsonRequestSender.h"

#include"router/router.h"

class userRequestSender : public QObject
{
    Q_OBJECT
public:
    explicit userRequestSender(QObject *parent = nullptr);

    //发送验证码
    void sendCaptcha(QString text);

    //发送注册功能
    void sendRegister(QString email,QString password,QString captcha);

    //发送登录申请
    void sendLogin(QString username,QString password);

private:
    JsonRequestSender* sender;
//使用发送器的那个窗口类
    QWidget* parentWidget;
signals:

};

#endif // USERREQUESTSENDER_H
