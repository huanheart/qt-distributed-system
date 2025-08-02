#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include<QWidget>
#include<QLine>
#include<QPushButton>
#include<QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QDebug>


#include"../../router/router.h"
#include"../../router/musicRouter.h"

#include"../../middleware/auth/Auth.h"

class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MusicPlayer(QObject *parent = nullptr);
    MusicPlayer()=default;

    using SuccessCallback = std::function<void()>;
    using FailCallback = std::function<void(const QString &)>;

    //设置音量
    void setVolume(int val);
    //设置远程音乐地址
    void setFileId(QString file_id);
    //设置本地音乐地址
    void setLocalFileId(QString file_path);

    //设置播放成功的回调函数
    void setSuccessFunc(SuccessCallback func);
    //设置播放失败的回调函数
    void setFailFunc(FailCallback func);

    //开始播放
    void startPlay();

    void pausePlay();

    void stopPlay();

    //设置音乐播放进度(以秒为单位）
    void setPosition(qint64 s);

    //静态成员函数，将当前时间转化成秒（todo)

public:


private:
    QMediaPlayer *player;
    //使用音乐播放器的那个窗口类
    QWidget* parentWidget;
    //成功和失败的回调函数
    SuccessCallback onSuccess;
    FailCallback onFail;

signals:

};




#endif
