#ifndef REGISTER_H
#define REGISTER_H


#include"../jsonRequest.hpp"


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



#endif
