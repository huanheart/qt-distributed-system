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
    //更新音乐时长
    ui->MusicTimer->setText(formatDuration(duration));
    //更新点赞数
    ui->MusicLikeCount->setText("点赞数: "+QString().number(like_count));
    //更新音乐名
    ui->MusicName->setText(QFileInfo(music_name).completeBaseName());
    //更新id号
    ui->label->setText(QString().number(id));
    //更新图片
    QString str = "QWidget{border-image:url("+url+");}";
    ui->widMusicPic->setStyleSheet(str);
    //更新点赞状态
    if(0==like_status){
        ui->like->setText("点赞");
    }else {
        ui->like->setText("取消点赞");
    }
}

void NewCourierItem::setMusicLikeCount(int like_count){
    this->like_count=like_count;
}
//设置timer
void NewCourierItem::setMusicTimer(double duration){
    this->duration=duration;
}
//表示未点赞状态
void NewCourierItem::setLikeStatus(){
    like_status=0;
}
//表示已点赞状态
void NewCourierItem::setFinishedLikeStatus(){
    like_status=1;
}
void NewCourierItem::HideLike(){
    ui->like->hide();  // 隐藏按钮
}
void NewCourierItem::ShowLike(){
    ui->like->show();  // 显示按钮
}

void NewCourierItem::HideMusicLikeCount(){
    ui->MusicLikeCount->hide();
}

void NewCourierItem::ShowMusicLikeCount(){
    ui->MusicLikeCount->show();
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


void NewCourierItem::on_like_clicked()
{
    emit Like(file_id);
}

