#ifndef FINDMUSIC_H
#define FINDMUSIC_H

#include <QWidget>
#include<QString>
#include<QJsonParseError>
#include<QString>
#include<QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>
#include<QUrlQuery>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>


#include"../../requestSender/musicRequestSender.h"
#include"../../requestSender/userrequestsender.h"

#include"../../func/utils/utils.h"
#include"newcourieritem.h"
#include"../../func/music/musicfunc.h"
#include"../../func/music/musicPlayer.h"



namespace Ui {
class findMusic;
}

class findMusic : public QWidget
{
    Q_OBJECT

public:
    explicit findMusic(QWidget *parent = nullptr);
    ~findMusic();

public:
    void DealFindMusic(bool ok,QString message,QJsonArray musicListArray);

    void DealDownLoadMusic(bool ok,QString message,QString file_id);

    void sendGetMusicInfos();

    void DealLikeInfos(bool ok,QString message,QStringList file_ids);

    void DealLike(bool ok,QString message,QString file_id,qint64 LikeCnt,qint64 LikeStatus);

public:

private:
    void AddItem();

private:
    musicRequestSender* music_sender=nullptr;
    userRequestSender* user_sender=nullptr;
    MusicPlayer *player;
    //维护一个自定义请求类型
    QMap<QString,QJsonObject> music_map;
    //通过file_id查询具体的指针，方便对指针内容进行修改操作
    QMap<QString,NewCourierItem*> Item_map;
    QStringList file_ids;
    int id;
    //这里先硬编码对应的请求多少cnt个数据了,后续整理一个config文件，将其存放
    //对应的token也存放到一个注册表中或指定文件中了
    int cnt=5;

private:
    //下载音乐所需要保存到的文件路径
    //todo:由于其它模块也会用到这个路径，固然得将其抽离出来
    QString save_path="D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\request\\";
    QString file_info=save_path+"file_info.json";
private:
    Ui::findMusic *ui;
};

#endif // FINDMUSIC_H
