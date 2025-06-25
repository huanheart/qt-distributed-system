#include"login.h"


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
