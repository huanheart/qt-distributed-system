#include"userRouter.h"



QString userRouter::GetRegisterPath(){
    return user_path+register_path;
}

QString userRouter::GetLoginPath(){
    return user_path+login_path;
}

QString userRouter::GetCaptchaPath(){
    return user_path+captcha_path;
}

