#include"jsonRequestSender.h"


void JsonRequestSender::resetData(){
    back_data.clear();
    Error.clear();
    is_success = true;
}


void JsonRequestSender::sendPostRequest(const QUrl &url, const JsonRequest &request,SuccessCallback onSuccess,FailureCallback onFail) {
    //使用抽象方法
    QMap<QString, QVariant> map = request.toMap();
    QJsonObject obj;
    for (auto it = map.begin(); it != map.end(); ++it) {
        obj[it.key()] = QJsonValue::fromVariant(it.value());
    }
    QJsonDocument doc(obj);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //发送post请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(req, jsonData);

    //使用异步信号槽机制
    connect(reply, &QNetworkReply::finished, this, [this, reply, onSuccess, onFail]() {
        if (reply->error() == QNetworkReply::NoError) {
//            emit requestSuccess(responseData);
            onSuccess(reply->readAll());
        } else {
//            emit requestFailed(reply->errorString());
            onFail(reply->errorString());
        }
        reply->deleteLater();
    });
}



void JsonRequestSender::sendGetRequest(const QUrl &url, const JsonRequest &request,SuccessCallback onSuccess,FailureCallback onFail) {
    // 构造带参数的 URL
    QUrl urlWithParams = url;
    QMap<QString, QVariant> map = request.toMap();
    QUrlQuery query;
    for (auto it = map.begin(); it != map.end(); ++it) {
        query.addQueryItem(it.key(), it.value().toString());
    }
    //设置GET参数
    urlWithParams.setQuery(query);

    QNetworkRequest req(urlWithParams);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(req);

    connect(reply, &QNetworkReply::finished, this, [this, reply, onSuccess, onFail]() {
        if (reply->error() == QNetworkReply::NoError) {
//            emit requestSuccess(responseData);
            onSuccess(reply->readAll());
        } else {
//            emit requestFailed(reply->errorString());
            onFail(reply->errorString());
        }
        reply->deleteLater();
    });
}

