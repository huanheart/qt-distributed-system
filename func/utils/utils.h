#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include<QWidget>
#include <QString>
#include <QFileInfo>
#include <QSet>



class Util :public QObject
{
    Q_OBJECT

public:

    static Util* GetInstance() {
        static Util instance;
        return &instance;
    }
    //判断当前是否为音乐类型文件，如mp3这些文件
    bool isMusicFile(QString file);

private:
    Util()=default;
    QString token;
private:


signals:

};





#endif
