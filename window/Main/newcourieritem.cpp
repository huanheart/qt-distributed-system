#include "newcourieritem.h"
#include "ui_newcourieritem.h"

NewCourierItem::NewCourierItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewCourierItem)
{
    ui->setupUi(this);
}

//设置id
void NewCourierItem::setNum(int id){
    this->id=id;
}
////设置图片
void NewCourierItem::setPicture(QString url){
    this->url=url;
}
////设置作者
//void NewCourierItem::setMusicAuthor(QString author){

//}

//设置歌名
void NewCourierItem::setMusicName(QString musicName){
    this->music_name=musicName;
}
//设置log 默认
void NewCourierItem::setLogPic(){
    ui->labMusicLog->setMaximumSize(27,17);
}

void NewCourierItem::display(){
    ui->MusicTimer->setText(formatDuration(duration));
    ui->MusicLikeCount->setText("点赞数: "+QString().number(like_count));
    ui->MusicName->setText(QFileInfo(music_name).completeBaseName());
    ui->label->setText(QString().number(id));
    QString str = "QWidget{border-image:url("+url+");}";
    ui->widMusicPic->setStyleSheet(str);
}

void NewCourierItem::setMusicLikeCount(int like_count){
    this->like_count=like_count;
}
//设置timer
void NewCourierItem::setMusicTimer(double duration){
    this->duration=duration;
}

void NewCourierItem::setFinishedDownloadStatus(){
    ui->download->setText("已下载");
    ui->download->setEnabled(false);
}

void NewCourierItem::setDownloadStatus(){
    ui->download->setText("下载");
    ui->download->setEnabled(true);
}

void NewCourierItem::setUserID(int user_id){
    this->user_id=user_id;
}
void NewCourierItem::setFileSize(int file_size){
    this->file_size=file_size;
}
void NewCourierItem::setFileID(QString file_id){
    this->file_id=file_id;
}
void NewCourierItem::setFilePath(QString file_path){
    this->file_path=file_path;
}


NewCourierItem::~NewCourierItem()
{
    delete ui;
}

void NewCourierItem::on_download_clicked()
{
    emit download(file_id);
}

//注意
void NewCourierItem::on_play_clicked()
{
    //用于远程音乐的信号
    emit playMusic(file_id);
    //用于本地音乐的信号
    emit playLocalMusic(file_id+"."+QFileInfo(music_name).suffix());
}

