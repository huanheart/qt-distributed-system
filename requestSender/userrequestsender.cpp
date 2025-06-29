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
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "验证码请求失败：" +error_msg);
                return ;
            }
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
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "注册请求失败：" +error_msg);
                return ;
            }
            // ✅ 新增字段解析
            qint64 userId = obj.value("user_id").toVariant().toLongLong();
            QString token = obj.value("token").toString();
            qDebug() << "用户ID：" << userId << ", token：" << token;

            //将 token 和 userId 保存下来，用于后续请求
            InformationManager::GetInstance()->setUserId(userId);
            AuthManager::GetInstance()->setToken(token);

            QMessageBox::information(parentWidget, "注册成功", "欢迎加入，您的用户ID是：" + QString::number(userId));

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
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "登录请求失败：" +error_msg);
                return ;
            }
            qint64 userId = obj.value("user_id").toVariant().toLongLong();
            QString token = obj.value("token").toString();
            //将 token 和 userId 保存下来，用于后续请求
            InformationManager::GetInstance()->setUserId(userId);
            AuthManager::GetInstance()->setToken(token);
            QMessageBox::information(parentWidget, "登录成功", "欢迎：" + QString::number(userId)+"号用户" );
        },

        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        }
    );
}

void userRequestSender::sendLike(QString file_id){
    UserLikeRequest request;
    request.setRequest(file_id);

    //发送请求
    sender->sendPostRequest(
        Router::GetInstance()->GetLikePath(),
        request,

        // 成功回调
        [this](const QByteArray &data) {
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "点赞失败：" +error_msg);
                return ;
            }

            qint64 LikeCnt = obj.value("like_count").toVariant().toLongLong();
            qint64 LikeStatus = obj.value("like_status").toVariant().toLongLong();

            //todo:后续需要发送信号/便于渲染到界面中
            qDebug()<<"likeCnt is "<<LikeCnt<<" and LikeStatus is "<<LikeStatus;

            QMessageBox::information(parentWidget, "点赞成功", "点赞成功");
        },

        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "点赞请求失败", "网络错误：" + error);
        }
    );
}

