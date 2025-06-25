
#ifndef USERROUTER_H
#define USERROUTER_H

#include<QString>

using namespace std;

class userRouter{

public:

    static userRouter* GetInstance(){
        static userRouter r;
        return &r;
    }
    QString GetRegisterPath();
    QString GetLoginPath();
    QString GetCaptchaPath();

private:
    //顶级目录
    QString user_path="/user";
private:
    QString register_path="/register";
    QString login_path="/login";
    QString captcha_path="/captcha";

private:

    userRouter()=default;
    userRouter(const userRouter&)=delete;
    userRouter& operator=(const userRouter&) = delete;

};






#endif
