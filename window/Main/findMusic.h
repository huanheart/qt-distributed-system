#ifndef FINDMUSIC_H
#define FINDMUSIC_H

#include <QWidget>
#include<QString>
#include<QJsonParseError>
#include<QString>
#include<QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>
#include<QUrlQuery>

#include"../../requestSender/musicRequestSender.h"

namespace Ui {
class findMusic;
}

class findMusic : public QWidget
{
    Q_OBJECT

public:
    explicit findMusic(QWidget *parent = nullptr);
    ~findMusic();

public:
    //维护一个自定义请求类型
    QMap<int,QJsonArray> music_map;

private:
    musicRequestSender* music_sender=nullptr;
private:
    Ui::findMusic *ui;
};

#endif // FINDMUSIC_H
