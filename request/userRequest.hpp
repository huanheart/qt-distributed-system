
#ifndef USERREQUEST_H
#define USERREQUEST_H


#include "jsonRequest.hpp"

class UserLoginRequest : public JsonRequest{

public:
    UserLoginRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QString username,QString password);
private:
    QString username;
    QString password;
};

QMap<QString,QVariant> UserLoginRequest::toMap() const {
    return {
        {"username", username},
        {"password", password}
    };
}

void UserLoginRequest::setRequest(QString username,QString password){
    this->username=username;
    this->password=password;
}


class UserRegisterRequest : public JsonRequest{

public:
    UserRegisterRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QString email,QString password,QString captcha);
private:
    QString email;
    QString captcha;
    QString password;
};

QMap<QString,QVariant> UserRegisterRequest::toMap() const{
    return {
        {"email", email},
        {"captcha", captcha},
        {"password", password}
    };
}

void UserRegisterRequest::setRequest(QString email,QString password,QString captcha){
    this->captcha=captcha;
    this->email=email;
    this->password=password;
}

//start

class UserCaptchaRequest : public JsonRequest{

public:
    UserCaptchaRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QString email);
private:
    QString email;
};

QMap<QString,QVariant> UserCaptchaRequest::toMap() const{
    return {
        {"email", email}
    };
}

void UserCaptchaRequest::setRequest(QString email){
    this->email=email;
}



#endif
