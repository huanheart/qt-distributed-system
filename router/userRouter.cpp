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

QString userRouter::GetLikePath(){
    return login_path+like_path;
}

QString userRouter::GetLikeInfosPath(){
    return login_path+like_infos_path;
}

