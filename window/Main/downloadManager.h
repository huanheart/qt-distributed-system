#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

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
#include<QFileInfo>

#include<QListWidgetItem>
#include"newcourieritem.h"

#include"../../func/music/musicfunc.h"
#include"../../func/music/musicPlayer.h"

namespace Ui {
class DownloadManager;
}

class DownloadManager : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadManager(QWidget *parent = nullptr);


    ~DownloadManager();
    void LoadFileInfo();
private:
    void removeUUIDFromItem_mapAndlist(QString baseName);
    void removeUUIDFromFile(QString baseName);
public:
    void onFileDeleteChanged(const QString &path);

private:
    //下载音乐所需要保存到的文件路径
    //todo:由于其它模块也会用到这个路径，固然得将其抽离出来
    QString save_path="D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\request\\";
    QString file_info=save_path+"file_info.json";
    MusicPlayer *player=nullptr;
    QMap<QString,QJsonObject> music_map;
    QMap<QString,NewCourierItem*> Item_map;
    Ui::DownloadManager *ui;
};

#endif // DOWNLOADMANAGER_H
