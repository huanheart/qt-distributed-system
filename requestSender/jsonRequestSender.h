#ifndef JSONREQUESTSENDER_H
#define JSONREQUESTSENDER_H

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
#include<QJsonArray>

#include"../middleware/auth/Auth.h"
#include"../request/jsonRequest.hpp"

class JsonRequestSender :public QObject{

private:
    Q_OBJECT
public:
    explicit JsonRequestSender(QObject *parent = nullptr) : QObject(parent) {}
    JsonRequestSender()=default;

    //绑定特定的回调函数，针对不同的响应做回调处理
    using SuccessCallback = std::function<void(const QByteArray &)>;
    using FailureCallback = std::function<void(const QString &)>;


    void sendPostRequest(const QUrl &url, const JsonRequest &request,SuccessCallback onSuccess,FailureCallback onFail);

    void sendGetRequest(const QUrl &url, const JsonRequest &request,SuccessCallback onSuccess,FailureCallback onFail);


public:
    QByteArray back_data;
    bool is_success;
    QString Error;

};

#endif
