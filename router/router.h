#ifndef ROUTER_H
#define ROUTER_H


#include<iostream>
#include<QString>
#include<unordered_map>

#include"musicRouter.h"
#include"userRouter.h"

using namespace std;


//这边设置成一个单例类
//这边先弄成硬编码形式
//后续需要配置解析文件

class Router
{
public:
    QString GetRouterPath(){
        return server_ip+QString(port)+version;
    }
    //用户相关api
    QString GetRegisterPath();
    QString GetLoginPath();
    QString GetCaptchaPath();
    //音乐相关api
    QString GetMusicUploadPath();
    QString GetMusicDownloadPath();


    static Router* GetInstance(){
        static Router r;
        return &r;
    }

private:
    Router()=default;
    Roter(const Router&)=delete;
    Router& operator=(const Router&) = delete;

private:
    QString version="/api/v1";

    QString server_ip="http://192.168.1.15";
    int port=8000;

};



//这里这个表明用来存储对应的code
class HttpCodeStatus{

public:
    bool IsSuccess(int code);

    static HttpCodeStatus* GetInstance(){
        static HttpCodeStatus r;
        return &r;
    }
    unordered_map<int,QString> codeMap;
private:
    const int success_code=1000;
    HttpCodeStatus();
    HttpCodeStatus(const Router&)=delete;
    HttpCodeStatus& operator=(const HttpCodeStatus&) = delete;

};





#endif // ROUTER_H
