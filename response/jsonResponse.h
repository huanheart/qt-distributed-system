#ifndef JSONRESPONSE_H
#define JSONRESPONSE_H

#include<QJsonParseError>
#include<QString>
#include<QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>
#include <QMap>
#include<QUrlQuery>

#include"../router/router.h"

//通用解析json响应数据的类
class JsonResponse{

private:

public:
    JsonResponse()=default;

    QJsonObject parse(const QByteArray &data,QString &error_msg);


};

#endif
