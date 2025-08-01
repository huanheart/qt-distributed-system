#ifndef MUSICFUNC_H
#define MUSICFUNC_H

#include <QObject>
#include<QString>
#include<QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>
#include <QMap>
#include<QUrlQuery>
#include<QMessageBox>
#include<QFileInfo>

class MusicFunc : public QObject
{
    Q_OBJECT
public:
    explicit MusicFunc(QObject *parent = nullptr);
    void setMusicParent(QObject *parent);

    void downloadFile(const QUrl &fileUrl, const QString &file_name,const QString &saveDir);

//    static MusicFunc* GetInstance() {
//        static MusicFunc instance;
//        return &instance;
//    }

    //进行下载操作

signals:
    //file_id这个uuid方便进行回调操作
    void sendMusicDownloadInformation(bool ok,QString message,QString file_id);
private:

    //使用音乐播放器的那个窗口类
    QWidget* parentWidget;

signals:

};

#endif // MUSICFUNC_H
