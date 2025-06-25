#include"register.h"


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
