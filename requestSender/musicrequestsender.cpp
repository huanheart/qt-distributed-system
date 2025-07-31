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
                emit sendMusicDownloadInformation(false,"下载音乐文件错误：" +error_msg);
                return ;
            }
            //获取文件路径
            QString file_path = obj.value("file_path").toString();
            //先将其保存到全局配置中去
            InformationManager::GetInstance()->setHttpFilePath(file_path);
            //使用前一定要绑定需要用到这个对象的窗口，这样才能进行弹窗
            MusicFunc::GetInstance()->setMusicParent(parentWidget);
            MusicFunc::GetInstance()->downloadFile(InformationManager::GetInstance()->GetHttpFilePath(),file_id,save_path);
//            QMessageBox::information(parentWidget, "成功", "该文件的地址为: " +file_path);
            emit sendMusicDownloadInformation(true,"成功,该文件的地址为: " +file_path);
        },
        [this](const QString &error) {
            emit sendMusicDownloadInformation(false,"网络错误：" + error);
        });

}

void musicRequestSender::sendMusicUpload(QString file_path){

    //先对路径进行合法性校验
    if(false==Util::GetInstance()->isMusicFile(file_path) ){
        emit sendMusicUploadInformation(false,"错误,不能上传除音乐文件之外的文件");
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
                emit sendMusicUploadInformation(false,"上传音乐文件请求失败：" +error_msg);
                return ;
            }
            //获取file_id
            QString file_id = obj.value("file_id").toString();
            InformationManager::GetInstance()->setFileID(file_id);
            emit sendMusicUploadInformation(true,"成功,开始上传音乐文件音乐文件！");
        },
        // 失败回调
        [this](const QString &error) {
            emit sendMusicUploadInformation(false,"网络错误：" + error);
        },
        file_name,
        file_path);
}


void musicRequestSender::sendGetMusicInfos(int id,int cnt){
    MusicInfosRequest request;
    request.setRequest(id,cnt);
    json_sender->sendGetRequest(
        Router::GetInstance()->GetMusicInfosPath(),
        request,
        [this](const QByteArray &data) {
            JsonResponse response;
            QString error_msg="";
            QJsonObject obj=response.parse(data,error_msg);
            if(error_msg!=""){
                emit sendGetMusicInfosInformation(false,"获取cnt条数据失败" +error_msg,QJsonArray());
                return ;
            }
            //下面
            QJsonArray musicListArray = obj["music_info_list"].toArray();

            // 遍历音乐列表
            for (const QJsonValue &value : musicListArray) {
                QJsonObject musicObj = value.toObject();

                QString uuid = musicObj["uuid"].toString();
                qint64 userId = musicObj["user_id"].toVariant().toLongLong();
                QString musicName = musicObj["music_name"].toString();
                QString filePath = musicObj["file_path"].toString();
                qint64 likeCount = musicObj["like_count"].toVariant().toLongLong();
                qint64 fileSize = musicObj["file_size"].toVariant().toLongLong();
                double duration = musicObj["duration"].toDouble();

                qDebug() << "UUID:" << uuid;
                qDebug() << "User ID:" << userId;
                qDebug() << "Music Name:" << musicName;
                qDebug() << "File Path:" << filePath;
                qDebug() << "Like Count:" << likeCount;
                qDebug() << "File Size:" << fileSize;
                qDebug() << "Duration:" << duration;
            }
            //上面
            emit sendGetMusicInfosInformation(true,"获取热门数据成功",musicListArray);
        },
        [this](const QString &error) {
            emit sendGetMusicInfosInformation(false,"网络错误：" + error,QJsonArray());
        });
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
//                QMessageBox::warning(parentWidget, "错误", "获取热门数据失败：" +error_msg);
                emit sendGetHotMusicInformation(false,"获取热门数据失败：" +error_msg,QJsonArray());
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
            emit sendGetHotMusicInformation(true,"获取热门数据成功",musicListArray);
        },
        [this](const QString &error) {
            emit sendGetHotMusicInformation(false,"网络错误：" + error,QJsonArray());
        });

}




