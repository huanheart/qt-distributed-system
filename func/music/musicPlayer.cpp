#include"musicPlayer.h"


MusicPlayer::MusicPlayer(QObject *parent)
    : QObject{parent},parentWidget(qobject_cast<QWidget *>(parent))
{
    player=new QMediaPlayer(this);

    connect(player, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state) {
        qDebug() << "播放状态:" << state;
            if (state == QMediaPlayer::PlayingState && onSuccess) {
                onSuccess();
            }
    });

    connect(player,
            QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this,
            [this](QMediaPlayer::Error error) {
                QString err = player->errorString();
                qDebug() << "播放错误:" << error << err;
                    if (onFail) {
                        onFail(err);
                    }
            });
    setVolume(100);

}


//设置音量
void MusicPlayer::setVolume(int val){
    if(val>100)
        val=100;
    if(val<0)
        val=0;
    player->setVolume(val);
}
//设置远程音乐地址
void MusicPlayer::setFileId(QString file_id){
    //合并之后类似
    // http://192.168.15.1/api/music/stream?file_id=%1&token=%2
    QString url=Router::GetInstance()->GetMusicStreamPath()+"?file_id="+file_id+"&token="+AuthManager::GetInstance()->getToken();
    player->setMedia(QUrl(url) );
}
//设置本地音乐地址
void MusicPlayer::setLocalFileId(QString file_path){
    QUrl localUrl = QUrl::fromLocalFile(file_path);
    player->setMedia(localUrl);
}

//设置播放成功的回调函数
void MusicPlayer::setSuccessFunc(SuccessCallback func){
    onSuccess=func;
}
//设置播放失败的回调函数
void MusicPlayer::setFailFunc(FailCallback func){
    onFail=func;
}

//开始播放
void MusicPlayer::startPlay(){
    player->play();
}

void MusicPlayer::pausePlay(){
    player->pause();
}

void MusicPlayer::stopPlay(){
    player->stop();
}

void MusicPlayer::setPosition(qint64 s){
    player->setPosition(s*1000);
}










