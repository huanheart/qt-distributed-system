#include "controlTabWidget.h"
#include "ui_controlTabWidget.h"

controlTabWidget::controlTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controlTabWidget)
{
    ui->setupUi(this);
    init();
}

void controlTabWidget::init(){

    ui->tabWidget->tabBar()->setHidden(true);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(30,30,30));
    ui->tabWidget->setAutoFillBackground(true);
    ui->tabWidget->setPalette(palette);
    ui->tabWidget->tabBar()->setPalette(palette);

    connect(this,&controlTabWidget::sendGetMusicInfos,ui->find_music,&findMusic::sendGetMusicInfos);

}

void controlTabWidget::GetMusicInfos(){
    emit sendGetMusicInfos();
}

void controlTabWidget::receiveShowCurrentTab(int cur,int index){
    if(cur==0){
        ui->tabWidget->setCurrentIndex(index);
    }else if(cur==1){
        //todo:这里硬编码不太好，后续更改这个槽函数
        //这个6得更改
//        ui->tabWidget->setCurrentIndex(6+index);
    }else if(cur==2){
        qDebug()<<"收藏歌单暂且未做";
    }

}

controlTabWidget::~controlTabWidget()
{
    delete ui;
}
