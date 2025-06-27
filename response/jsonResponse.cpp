#include"jsonResponse.h"



QJsonObject JsonResponse::parse(const QByteArray &data,QString &error_msg){
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        error_msg=parseError.errorString();
        return {};
    }
    QJsonObject obj = doc.object();
    int statusCode = obj.value("status_code").toInt();
    QString statusMsg = obj.value("status_msg").toString();
    if (!HttpCodeStatus::GetInstance()->IsSuccess(statusCode)) {
        error_msg=statusMsg;
        return {};
    }
    return obj;
}
