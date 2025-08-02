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
    ui->MusicName->setText(music_name);

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


void NewCourierItem::on_play_clicked()
{
    emit playMusic(file_id);
}

