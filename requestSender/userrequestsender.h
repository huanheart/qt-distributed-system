#ifndef USERREQUESTSENDER_H
#define USERREQUESTSENDER_H

#include <QObject>
#include<QMessageBox>

#include"request/user/captcha.h"
#include"request/user/login.h"
#include"request/user/register.h"
#include"request/user/like.h"


#include"../middleware/auth/Auth.h"

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

    //为某一个音乐点赞
    void sendLike(QString file_id);

private:
    JsonRequestSender* sender;
//使用发送器的那个窗口类
    QWidget* parentWidget;
signals:

};

#endif // USERREQUESTSENDER_H
