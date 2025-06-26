#include "musicrequestsender.h"

musicRequestSender::musicRequestSender(QObject *parent)
    : QObject{parent},parentWidget(qobject_cast<QWidget *>(parent))
{
    json_sender = new JsonRequestSender(this);
    formdata_sender=new FormDataRequestSender(this);
}



void musicRequestSender::sendMusicDownload(QString file_id){
    MusicDownloadRequest request;
    request.setRequest(file_id);

    json_sender->sendPostRequest(
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

            QMessageBox::information(parentWidget, "成功", "开始上传音乐文件音乐文件！");
        },
        // 失败回调
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        },
        file_name,
        file_path);

}
