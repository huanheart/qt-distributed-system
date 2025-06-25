#ifndef CAPTCHA_H
#define CAPTCHA_H

#include"../jsonRequest.hpp"

class UserCaptchaRequest : public JsonRequest{

public:
    UserCaptchaRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QString email);
private:
    QString email;
};




#endif
