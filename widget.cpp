#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

void Widget::init(){
    ui->username->setPlaceholderText("请输入账号/邮箱");
    ui->password->setPlaceholderText("请输入密码");
    sender = new JsonRequestSender(this);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_login_clicked()
{

}


void Widget::on_register_2_clicked()
{

}



void Widget::on_captcha_clicked()
{
    UserCaptchaRequest request;
    request.setRequest(ui->username->text());

    sender->resetData();  // 每次调用必须清空旧状态

    sender->sendPostRequest(
        userRouter::GetInstance()->GetCaptchaPath(),
        request,
        //成功回调
        [this](const QByteArray &data) {
            QJsonParseError parseError;
            QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "解析 JSON 出错:" << parseError.errorString();
                QMessageBox::warning(this, "错误", "验证码响应 JSON 格式错误！");
                return;
            }
            QJsonObject obj = doc.object();
            int statusCode = obj.value("status_code").toInt();
            QString statusMsg = obj.value("status_msg").toString();

            if (!HttpCodeStatus::GetInstance()->IsSuccess(statusCode)) {
                QMessageBox::warning(this, "错误", "验证码请求失败：" + HttpCodeStatus::GetInstance()->codeMap[statusCode]);
                return ;
            }
            qDebug() << "验证码请求成功：" << statusMsg;
            QMessageBox::information(this, "验证码发送", "验证码已发送，请查收邮箱！");
        },
        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(this, "请求失败", "网络错误：" + error);
        }
    );

}
