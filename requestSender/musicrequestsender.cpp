#include "musicrequestsender.h"

musicRequestSender::musicRequestSender(QObject *parent)
    : QObject{parent},parentWidget(qobject_cast<QWidget *>(parent))
{
    json_sender = new JsonRequestSender(this);
    formdata_sender=new FormDataRequestSender(this);
}

void downloadFile(const QUrl &fileUrl, const QString &saveDir, QObject *context = nullptr) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(context);
    QNetworkRequest request(fileUrl);
    QNetworkReply *reply = manager->get(request);

    // 自动获取文件扩展名（如 .png, .jpg）
    QString suffix = QFileInfo(fileUrl.path()).suffix();
    if (suffix.isEmpty()) suffix = "jpg"; // 默认后缀

    QString savePath = saveDir + "/test." + suffix;
    QFile *file = new QFile(savePath);
    if (!file->open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开保存路径：" << savePath;
        QMessageBox::warning(nullptr, "错误", "无法打开文件路径进行保存！");
        delete file;
        manager->deleteLater();
        return;
    }

    // 写入数据
    QObject::connect(reply, &QNetworkReply::readyRead, context, [=]() {
        file->write(reply->readAll());
    });

    // 完成处理
    QObject::connect(reply, &QNetworkReply::finished, context, [=]() {
        file->flush();
        file->close();
        file->deleteLater();

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "下载成功：" << savePath;
            QMessageBox::information(nullptr, "下载完成", "图片下载成功！");
        } else {
            qDebug() << "下载失败：" << reply->errorString();
            QMessageBox::warning(nullptr, "下载失败", reply->errorString());
            QFile::remove(savePath); // 删除失败文件
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}

void musicRequestSender::sendMusicDownload(QString file_id){
    MusicDownloadRequest request;
    request.setRequest(file_id);

    json_sender->sendGetRequest(
        Router::GetInstance()->GetMusicDownloadPath(),
        request,
        [this](const QByteArray &data) {
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "下载音乐文件：" +error_msg);
                return ;
            }

            //获取file_id
            QString file_path = obj.value("file_path").toString();
            qDebug()<<"file_path is : "+file_path;
            //todo:需要将这个地址返回回去，然后再来就是请求这个文件并保存到一个指定路径下了

            //先将其保存到全局配置中去
            InformationManager::GetInstance()->setHttpFilePath(file_path);
            //直接在这里进行下载操作
            QString save_path="D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\request";
            qDebug()<<"http path is: "<<InformationManager::GetInstance()->GetHttpFilePath();

            downloadFile("http://"+InformationManager::GetInstance()->GetHttpFilePath(),save_path,parentWidget);

            QMessageBox::information(parentWidget, "成功", "该文件的地址为: " +file_path);
        },
        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        });

}

void musicRequestSender::sendMusicUpload(QString file_path){
    MusicUploadRequest request;
    request.setRequest();

    formdata_sender->sendPostRequest(
        Router::GetInstance()->GetMusicUploadPath(),
             request,
        //成功回调
        [this](const QByteArray &data) {
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "上传音乐文件请求失败：" +error_msg);
                return ;
            }

            //获取file_id
            QString file_id = obj.value("file_id").toString();
            qDebug()<<"file_id is : "+file_id;
            //todo:需要将这个file_id返回回去，可以用一个信号，后续需要填充到QLabel上渲染当前文件的uuid
            //这边先将file_id放到全局的配置中去
            InformationManager::GetInstance()->setFileID(file_id);

            QMessageBox::information(parentWidget, "成功", "开始上传音乐文件音乐文件！");
        },
        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        },
        file_name,
        file_path);
}




