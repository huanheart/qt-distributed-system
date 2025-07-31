#include "findMusic.h"
#include "ui_findMusic.h"

findMusic::findMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findMusic)
{
    ui->setupUi(this);
    music_sender=new musicRequestSender(this);
    //todo：这里封装具体的操作,用于将音乐信息维护起来
    connect(music_sender,&musicRequestSender::sendGetMusicInfosInformation,this,[=](bool ok,QString message,QJsonArray musicListArray){
        musicListArray;
    });

}

findMusic::~findMusic()
{
    delete ui;
}
