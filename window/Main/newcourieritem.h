#ifndef NEWCOURIERITEM_H
#define NEWCOURIERITEM_H

#include <QWidget>

namespace Ui {
class NewCourierItem;
}

class NewCourierItem : public QWidget
{
    Q_OBJECT

public:
    explicit NewCourierItem(QWidget *parent = nullptr);
    ~NewCourierItem();

    //设置图片(暂时不提供图片显示功能）
    void setPicture(QString url);

//    //设置作者（暂时不提供该功能）
//    void setMusicAuthor(QString author);


    //开始下面
    //将设置的值全部更新并展现出来
    void display();

    //设置音乐序列号id
    void setNum(int id);

    //设置歌名
    void setMusicName(QString musicName);
    //设置log 默认
    void setLogPic();
    //设置点赞数
    void setMusicLikeCount(int like_count);
    //设置音乐时长
    void setMusicTimer(double duration);
    //设置用户id
    void setUserID(int user_id);
    void setFileSize(int file_size);
    void setFileID(QString file_id);
    void setFilePath(QString file_path);

    int getLikeCount() const {
        return like_count;
    }

    int getFileSize() const {
        return file_size;
    }

    double getDuration() const {
        return duration;
    }

    QString getFileId() const {
        return file_id;
    }

    QString getMusicName() const {
        return music_name;
    }

    QString getFilePath() const {
        return file_path;
    }

signals:
    void download(QString file_id);
    void playMusic(QString file_id);
private slots:
    void on_download_clicked();

    void on_play_clicked();

private:
    QString formatDuration(double duration) {
        int minutes = static_cast<int>(duration) / 60;
        int seconds = static_cast<int>(duration) % 60;
        return QString("%1分%2秒").arg(minutes).arg(seconds, 2, 10, QChar('0'));
    }


private:
    //序列号
    int id;
    //用户id（谁发布的这个音乐）
    int user_id;
    //点赞数
    int like_count;
    //文件大小
    int file_size;
    //时长
    double duration;
    //文件uuid
    QString file_id;
    //音乐名
    QString music_name;
    //文件http的路径
    QString file_path;
    //图片(暂且不可以放图片）
    QString url;
    Ui::NewCourierItem *ui;
};

#endif // NEWCOURIERITEM_H
