#ifndef LOGIN_H
#define LOGIN_H

#include"../jsonRequest.hpp"

class UserLoginRequest : public JsonRequest{

public:
    UserLoginRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QString username,QString password);
private:
    QString username;
    QString password;
};




#endif
