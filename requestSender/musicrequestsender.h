#ifndef MUSICREQUESTSENDER_H
#define MUSICREQUESTSENDER_H

#include <QObject>


#include<QMessageBox>

#include"request/music/musicDownload.h"
#include"request/music/musicUpload.h"

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

signals:


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
