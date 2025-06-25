
#include"captcha.h"

QMap<QString,QVariant> UserCaptchaRequest::toMap() const{
    return {
        {"email", email}
    };
}

void UserCaptchaRequest::setRequest(QString email){
    this->email=email;
}



