#include "userrequestsender.h"

userRequestSender::userRequestSender(QObject *parent)
    : QObject(parent), parentWidget(qobject_cast<QWidget *>(parent))
{
    sender = new JsonRequestSender(this);
}



void userRequestSender::sendCaptcha(QString text){
    UserCaptchaRequest request;
    request.setRequest(text);

    sender->sendPostRequest(
        Router::GetInstance()->GetCaptchaPath(),
        request,
        //成功回调
        [this](const QByteArray &data) {
            QJsonParseError parseError;
            QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "解析 JSON 出错:" << parseError.errorString();
                QMessageBox::warning(parentWidget, "错误", "验证码响应 JSON 格式错误！");
                return;
            }
            QJsonObject obj = doc.object();
            int statusCode = obj.value("status_code").toInt();
            QString statusMsg = obj.value("status_msg").toString();

            if (!HttpCodeStatus::GetInstance()->IsSuccess(statusCode)) {
                QMessageBox::warning(parentWidget, "错误", "验证码请求失败：" + HttpCodeStatus::GetInstance()->codeMap[statusCode]);
                return ;
            }
            qDebug() << "验证码请求成功：" << statusMsg;
            QMessageBox::information(parentWidget, "验证码发送", "验证码已发送，请查收邮箱！");
        },
        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        }
    );
}

void userRequestSender::sendRegister(QString email, QString password, QString captcha) {
    UserRegisterRequest request;
    request.setRequest(email, password, captcha);

    sender->sendPostRequest(
        Router::GetInstance()->GetRegisterPath(),
        request,

        // 成功回调
        [this](const QByteArray &data) {
            QJsonParseError parseError;
            QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "解析 JSON 出错:" << parseError.errorString();
                QMessageBox::warning(parentWidget, "错误", "注册响应 JSON 格式错误！");
                return;
            }

            QJsonObject obj = doc.object();
            int statusCode = obj.value("status_code").toInt();
            QString statusMsg = obj.value("status_msg").toString();

            if (!HttpCodeStatus::GetInstance()->IsSuccess(statusCode)) {
                QMessageBox::warning(parentWidget, "错误", "注册失败：" + HttpCodeStatus::GetInstance()->codeMap[statusCode]);
                return;
            }

            // ✅ 新增字段解析
            qint64 userId = obj.value("user_id").toVariant().toLongLong();
            QString token = obj.value("token").toString();

            qDebug() << "注册成功：" << statusMsg;
            qDebug() << "用户ID：" << userId << ", token：" << token;

            QMessageBox::information(parentWidget, "注册成功", "欢迎加入，您的用户ID是：" + QString::number(userId));

            // todo:将 token 和 userId 保存下来，用于后续请求

        },

        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        }
    );
}

void userRequestSender::sendLogin(QString username,QString password){
    UserLoginRequest request;
    request.setRequest(username, password);

    //发送请求
    sender->sendPostRequest(
        Router::GetInstance()->GetLoginPath(),
        request,

        // 成功回调
        [this](const QByteArray &data) {
            QJsonParseError parseError;
            QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "解析 JSON 出错:" << parseError.errorString();
                QMessageBox::warning(parentWidget, "错误", "登录响应 JSON 格式错误！");
                return;
            }

            QJsonObject obj = doc.object();
            int statusCode = obj.value("status_code").toInt();
            QString statusMsg = obj.value("status_msg").toString();

            if (!HttpCodeStatus::GetInstance()->IsSuccess(statusCode)) {
                QMessageBox::warning(parentWidget, "错误", "登录失败：" + HttpCodeStatus::GetInstance()->codeMap[statusCode]);
                return;
            }

            // ✅ 新增字段解析
            qint64 userId = obj.value("user_id").toVariant().toLongLong();
            QString token = obj.value("token").toString();

            qDebug() << "登录成功：" << statusMsg;
            qDebug() << "用户ID：" << userId << ", token：" << token;

            QMessageBox::information(parentWidget, "登录成功", "欢迎：" + QString::number(userId)+"号用户" );

            // todo:将 token 和 userId 保存下来，用于后续请求

        },

        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        }
    );
}


