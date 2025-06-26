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
    ui->cap->setPlaceholderText("请输入验证码");
    ui->file_id->setPlaceholderText("请输入指定的file_id");
    user_sender=new userRequestSender(this);
    music_sender=new musicRequestSender(this);

}

Widget::~Widget()
{
    delete ui;
}

//下面信号槽都是当前测试接口用的
//void downloadFile(const QUrl &fileUrl, const QString &savePath, QObject *context = nullptr) {
//    QNetworkAccessManager *manager = new QNetworkAccessManager(context);
//    QNetworkRequest request(fileUrl);
//    QNetworkReply *reply = manager->get(request);

//    QFile *file = new QFile(savePath);
//    if (!file->open(QIODevice::WriteOnly)) {
//        qWarning() << "无法打开保存路径：" << savePath;
//        QMessageBox::warning(nullptr, "错误", "无法打开文件路径进行保存！");
//        delete file;
//        manager->deleteLater();
//        return;
//    }

//    // 写入数据
//    QObject::connect(reply, &QNetworkReply::readyRead, context, [=]() {
//        file->write(reply->readAll());
//    });

//    // 完成处理
//    QObject::connect(reply, &QNetworkReply::finished, context, [=]() {
//        file->flush();
//        file->close();
//        file->deleteLater();

//        if (reply->error() == QNetworkReply::NoError) {
//            qDebug() << "下载成功：" << savePath;
//            QMessageBox::information(nullptr, "下载完成", "文件下载成功！");
//        } else {
//            qDebug() << "下载失败：" << reply->errorString();
//            QMessageBox::warning(nullptr, "下载失败", reply->errorString());
//        }

//        reply->deleteLater();
//        manager->deleteLater();
//    });
//}







void Widget::on_login_clicked()
{
    user_sender->sendLogin(ui->username->text(),ui->password->text());
}


void Widget::on_register_2_clicked()
{
    user_sender->sendRegister(ui->username->text(),ui->password->text(),ui->cap->text());
}



void Widget::on_captcha_clicked()
{
    user_sender->sendCaptcha(ui->username->text());
}

void Widget::on_download_clicked()
{
    music_sender->sendMusicDownload(InformationManager::GetInstance()->GetFileID() );
    //然后我们需要进行一个下载操作，我们先将其保存到全局变量中，后续将其渲染到对应的界面上去
}


void Widget::on_upload_clicked()
{
    music_sender->sendMusicUpload("D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\photo\\test.png");
}

