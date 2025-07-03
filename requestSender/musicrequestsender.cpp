#include "musicrequestsender.h"



musicRequestSender::musicRequestSender(QObject *parent)
    : QObject{parent},parentWidget(qobject_cast<QWidget *>(parent))
{
    json_sender = new JsonRequestSender(this);
    formdata_sender=new FormDataRequestSender(this);
}


void musicRequestSender::sendMusicDownload(QString file_id,QString save_path){
    MusicDownloadRequest request;
    request.setRequest(file_id);

    json_sender->sendGetRequest(
        Router::GetInstance()->GetMusicDownloadPath(),
        request,
        [this,file_id,save_path](const QByteArray &data) {
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "下载音乐文件：" +error_msg);
                return ;
            }
            //获取文件路径
            QString file_path = obj.value("file_path").toString();
            //先将其保存到全局配置中去
            InformationManager::GetInstance()->setHttpFilePath(file_path);
            //使用前一定要绑定需要用到这个对象的窗口，这样才能进行弹窗
            MusicFunc::GetInstance()->setMusicParent(parentWidget);
            MusicFunc::GetInstance()->downloadFile(InformationManager::GetInstance()->GetHttpFilePath(),file_id,save_path);

            QMessageBox::information(parentWidget, "成功", "该文件的地址为: " +file_path);
        },
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        });

}

void musicRequestSender::sendMusicUpload(QString file_path){

    //先对路径进行合法性校验
    if(false==Util::GetInstance()->isMusicFile(file_path) ){
        QMessageBox::warning(parentWidget, "错误", "不能上传除音乐文件之外的文件");
        return ;
    }

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

void musicRequestSender::sendGetHotMusic(){
    HotMusicRequest request;
    request.setRequest();

    json_sender->sendGetRequest(
        Router::GetInstance()->GetHotMusicPath(),
        request,
        [this](const QByteArray &data) {
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                QMessageBox::warning(parentWidget, "错误", "获取热门数据失败：" +error_msg);
                return ;
            }
            //开始获取这个json数组数据
            QJsonArray musicListArray = obj["music_list"].toArray();
            // 遍历音乐列表
            for (const QJsonValue &value : musicListArray) {
                QJsonObject musicObj = value.toObject();
                QString filePath = musicObj["file_path"].toString();
                int likeCount = musicObj["like_count"].toInt();

                qDebug() << "File Path:" << filePath;
                qDebug() << "Like Count:" << likeCount;
            }
        },
        [this](const QString &error) {
            QMessageBox::warning(parentWidget, "请求失败", "网络错误：" + error);
        });

}




