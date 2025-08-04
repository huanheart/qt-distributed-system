#include "LeftList.h"
#include "ui_LeftList.h"

#include<QDebug>

LeftList::LeftList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftList)
{
    ui->setupUi(this);
    setListT1();
    setListT2();
    //注意：list3是创建歌单的，固然不用一开始就添加一些内容上去
    //todo：后续要做成网络拉取歌单状态，提前在初始化阶段创建好
    connect(ui->list1, &QListWidget::itemClicked, this, [&](QListWidgetItem *item){
        int index = ui->list1->row(item);
//        qDebug()<<"页面1被点击了,具体元素下标为 "<<index;
        emit LeftListClicked_1(0,index);
    });
    connect(ui->list2, &QListWidget::itemClicked, this, [&](QListWidgetItem *item){
        int index = ui->list2->row(item);
//        qDebug()<<"页面2被点击了,具体元素下标为 "<<index;
        emit LeftListClicked_2(1,index);
    });
    connect(ui->list3, &QListWidget::itemClicked, this, [&](QListWidgetItem *item){
        int index = ui->list3->row(item);
//        qDebug()<<"页面3被点击了,具体元素下标为 "<<index;
        emit LeftListClicked_3(2,index);
    });

}


void LeftList::setListT1(){
    ui->list1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->list1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QListWidgetItem *findMusic = new QListWidgetItem(ui->list1);
    findMusic->setText("发现音乐");
    QListWidgetItem *podcast = new QListWidgetItem(ui->list1);
    podcast->setText("播客");
    QListWidgetItem *video = new QListWidgetItem(ui->list1);
    video->setText("视频");
    QListWidgetItem *friends = new QListWidgetItem(ui->list1);
    friends->setText("朋友");
    QListWidgetItem *live = new QListWidgetItem(ui->list1);
    live->setText("直播");
    QListWidgetItem *pcFM = new QListWidgetItem(ui->list1);
    pcFM->setText("私人FM");
}

void LeftList::setListT2(){
    // 取消滚动条
    ui->list2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->list2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 创建并添加列表项
    QListWidgetItem *likeMusic = new QListWidgetItem(ui->list2);
    likeMusic->setText("我喜欢的音乐");

    QListWidgetItem *recentPlay = new QListWidgetItem(ui->list2);
    recentPlay->setText("最近播放");

    QListWidgetItem *download = new QListWidgetItem(ui->list2);
    download->setText("下载管理");

    QListWidgetItem *myFav = new QListWidgetItem(ui->list2);
    myFav->setText("我的收藏");

    QListWidgetItem *localMusic = new QListWidgetItem(ui->list2);
    localMusic->setText("本地音乐");


}

LeftList::~LeftList()
{
    delete ui;
}
