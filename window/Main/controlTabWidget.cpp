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

controlTabWidget::~controlTabWidget()
{
    delete ui;
}
