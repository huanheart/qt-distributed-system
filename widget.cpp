#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

void Widget::init(){
    ui->username->setPlaceholderText("请输入账号/邮箱");
    ui->password->setPlaceholderText("请输入密码");
    ui->cap->setPlaceholderText("请输入验证码");
    ui->file_id->setPlaceholderText("请输入指定的file_id");
    user_sender=new userRequestSender(this);
    music_sender=new musicRequestSender(this);
    player = new MusicPlayer(this);
}

Widget::~Widget()
{
    delete ui;
}




//下面信号槽都是当前测试接口用的
void Widget::playRemoteMusic(const QString &fileID) {

    player->setFileId(fileID);
    //这边先不用设置回调了，直接进行播放就可以了
//    player->setSuccessFunc();
//    player->setFailFunc();
    player->startPlay();  // 开始播放
}


void Widget::on_login_clicked()
{
    user_sender->sendLogin(ui->username->text(),ui->password->text());
}


void Widget::on_register_2_clicked()
{
    user_sender->sendRegister(ui->username->text(),ui->password->text(),ui->cap->text());
}



void Widget::on_captcha_clicked()
{
    user_sender->sendCaptcha(ui->username->text());
}

void Widget::on_download_clicked()
{
    music_sender->sendMusicDownload(InformationManager::GetInstance()->GetFileID() );
    //然后我们需要进行一个下载操作，我们先将其保存到全局变量中，后续将其渲染到对应的界面上去
}


void Widget::on_upload_clicked()
{
//    music_sender->sendMusicUpload("D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\photo\\test.png");
    music_sender->sendMusicUpload("D:\\CloudMusic\\music.mp3");
}

//测试对应播放音乐的接口
void Widget::on_startMusic_clicked()
{
    playRemoteMusic(ui->file_id->text());

}


void Widget::on_pos_clicked()
{
    player->setPosition(ui->pos_line->text().toInt());
}

