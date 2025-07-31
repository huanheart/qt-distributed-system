#ifndef MUSICREQUESTSENDER_H
#define MUSICREQUESTSENDER_H

#include <QObject>


#include<QMessageBox>

#include"request/music/musicDownload.h"
#include"request/music/musicUpload.h"
#include"request/music/hotMusic.h"
#include"request/music/musicInfos.h"

#include"../response/jsonResponse.h"

#include"formdatarequestsender.h"
#include"jsonRequestSender.h"

#include"router/router.h"

#include"../func/music/musicfunc.h"
#include"../func/utils/utils.h"

class musicRequestSender : public QObject
{
    Q_OBJECT
public:
    explicit musicRequestSender(QObject *parent = nullptr);

    void sendMusicDownload(QString file_id,QString save_path);

    void sendMusicUpload(QString file_path);

    void sendGetHotMusic();

    //todo:参数暂未确定，用于获取大于等于id的前cnt个字符
    void sendGetMusicInfos(int id,int cnt);

signals:
    void sendMusicDownloadInformation(bool ok,QString message);

    void sendMusicUploadInformation(bool ok,QString message);

    void sendGetHotMusicInformation(bool ok,QString message,QJsonArray musicListArray);
    //todo:参数暂未确定，可能需要返回一个json数组，添加到使用者的map中，以及更新max_id
    void sendGetMusicInfosInformation(bool ok,QString message,QJsonArray musicListArray);

private:
    //由于它需要请求form-data的相关接口
    //又存在发送json的接口，固然需要两个发送器
    FormDataRequestSender * formdata_sender;
    JsonRequestSender* json_sender;
    //使用发送器的那个窗口类
    QWidget* parentWidget;

    //这里定死了字段名,传输的文件字段名
    QString file_name="file";

};

#endif // MUSICREQUESTSENDER_H
