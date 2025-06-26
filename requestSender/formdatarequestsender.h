#ifndef FORMDATAREQUESTSENDER_H
#define FORMDATAREQUESTSENDER_H

#include <QObject>
#include<QHttpMultiPart>
#include<QFile>
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
#include<QFileInfo>
#include<QNetworkRequest>


#include"../middleware/auth/Auth.h"
#include"../request/formDataRequest.hpp"

class FormDataRequestSender : public QObject
{
    Q_OBJECT
public:
    explicit FormDataRequestSender(QObject *parent = nullptr);
    FormDataRequestSender()=default;

    //绑定特定的回调函数，针对不同的响应做回调处理
    using SuccessCallback = std::function<void(const QByteArray &)>;
    using FailureCallback = std::function<void(const QString &)>;

    //封装post请求，
    void sendPostRequest(const QUrl &url, const FormDataRequest &request,
                         SuccessCallback onSuccess,FailureCallback onFailure,
                         const QString &fileFieldName,const QString &filePath);


public:


private:

signals:

};

#endif // FORMDATAREQUESTSENDER_H
