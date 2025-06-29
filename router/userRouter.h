
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
    QString GetLikePath();
private:
    //顶级目录
    QString user_path="/user";
    //登录之后相关用户的目录
    QString login_path="/login";
private:
    QString register_path="/register";
    QString login_path="/login";
    QString captcha_path="/captcha";

    //登录后相关用户目录
    QString like_path="/like";

private:

    userRouter()=default;
    userRouter(const userRouter&)=delete;
    userRouter& operator=(const userRouter&) = delete;

};






#endif
