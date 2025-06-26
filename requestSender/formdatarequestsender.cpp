#include "formdatarequestsender.h"

FormDataRequestSender::FormDataRequestSender(QObject *parent)
    : QObject{parent}
{

}

void FormDataRequestSender::sendPostRequest(const QUrl &url, const FormDataRequest &formdata_request,
                                            SuccessCallback onSuccess,FailureCallback onFailure,
                                            const QString &fileFieldName,const QString &filePath){
    QMap<QString, QVariant> fields =formdata_request.toMap();
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // 添加表单字段
    //补充（QHttpPart 只能设置 QByteArray，需要你自己转换类型）
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QString("form-data; name=\"%1\"").arg(it.key()));

        QJsonValue val = QJsonValue::fromVariant(it.value());
        QByteArray body;

        if (val.isBool()) {
            body = val.toBool() ? "true" : "false";
        } else if (val.isDouble()) {
            body = QByteArray::number(val.toDouble());
        } else if (val.isString()) {
            body = val.toString().toUtf8();
        } else {
            body = it.value().toString().toUtf8(); // fallback
        }

        textPart.setBody(body);
        multiPart->append(textPart);
    }

    //添加文件部分（这里默认添加单个文件）
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        onFailure("无法打开文件：" + filePath);
        delete file;
        multiPart->deleteLater();
        return;
    }

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"%1\"; filename=\"%2\"")
                           .arg(fileFieldName, QFileInfo(*file).fileName()));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    // 3. 设置请求（附带 token）
    QNetworkRequest request(url);



    QString token = AuthManager::GetInstance()->getToken();  // 自己实现的 token 管理器
    if (!token.isEmpty()) {
        request.setRawHeader("Authorization", "Bearer " + token.toUtf8());
    }

    // 4. 发起请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);  // 自动释放

    // 5. 异步处理响应
    connect(reply, &QNetworkReply::finished, this, [reply, onSuccess, onFailure]() {
        if (reply->error() == QNetworkReply::NoError) {
            onSuccess(reply->readAll());
        } else {
            onFailure(reply->errorString());
        }
        reply->deleteLater();
    });

}
