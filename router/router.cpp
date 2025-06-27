#include "router.h"


bool HttpCodeStatus::IsSuccess(int code){
    return success_code==code;
}

HttpCodeStatus::HttpCodeStatus(){
    codeMap[1000] = "CodeSuccess";
    codeMap[2001] = "CodeInvalidParams";
    codeMap[2002] = "CodeUserExist";
    codeMap[2003] = "CodeUserNotExist";
    codeMap[2004] = "CodeInvalidPassword";
    codeMap[2005] = "CodeNotMatchPassword";
    codeMap[2006] = "CodeInvalidToken";
    codeMap[2007] = "CodeNotLogin";
    codeMap[2008] = "CodeInvalidCaptcha";
    codeMap[2009] = "CodeRecordNotFound";
    codeMap[2010] = "CodeSubmitNotFound";
    codeMap[2011] = "CodeNotRegistred";
    codeMap[2012] = "CodeAlreadyRegistered";
    codeMap[2013] = "CodeContestNotStarted";
    codeMap[2014] = "CodeContestHasStarted";
    codeMap[2015] = "CodeContestNotExist";
    codeMap[2016] = "CodeContestNotOngoing";
    codeMap[2017] = "CodeIllegalPassword";
    codeMap[3001] = "CodeForbidden";
    codeMap[4001] = "CodeServerBusy";
    codeMap[5001] = "FileNotFind";
}


//用户相关api
QString Router::GetRegisterPath(){
    return GetRouterPath()+userRouter::GetInstance()->GetRegisterPath();
}
QString Router::GetLoginPath(){
    return GetRouterPath()+userRouter::GetInstance()->GetLoginPath();
}
QString Router::GetCaptchaPath(){
//    qDebug()<<GetRouterPath()+userRouter::GetInstance()->GetCaptchaPath();
    return GetRouterPath()+userRouter::GetInstance()->GetCaptchaPath();
}

//音乐相关api
QString Router::GetMusicUploadPath(){
    return GetRouterPath()+musicRouter::GetInstance()->GetMusicUploadPath();
}
QString Router::GetMusicDownloadPath(){
    return GetRouterPath()+musicRouter::GetInstance()->GetMusicDownloadPath();
}

QString Router::GetMusicStreamPath(){
    //   http://192.168.15.1:8000/api/v1/music/stream
    return GetRouterPath()+musicRouter::GetInstance()->GetMusicStreamPath();
}

