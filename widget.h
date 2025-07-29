#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include<QLine>
#include<QPushButton>
#include<QMessageBox>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QDebug>


#include"request/user/captcha.h"
#include"request/user/login.h"
#include"request/user/register.h"


#include"router/userRouter.h"
#include"router/musicRouter.h"

#include"router/router.h"

#include"requestSender/userrequestsender.h"
#include"requestSender/musicrequestsender.h"

#include"func/music/musicPlayer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    void init();

private:
    Widget(QWidget *parent = nullptr);
public:
    static Widget* GetMainWindow() {
        static Widget instance;
        return &instance;
    }

    ~Widget();
    userRequestSender* user_sender=nullptr;

    musicRequestSender* music_sender=nullptr;

    void playRemoteMusic(const QString &fileID);

signals:

private slots:
    void on_login_clicked();

    void on_register_2_clicked();


    void on_captcha_clicked();

    void on_download_clicked();

    void on_upload_clicked();

    void on_startMusic_clicked();

    void on_pos_clicked();

    void on_like_clicked();

    void on_HotData_clicked();

private:
    Ui::Widget *ui;

    MusicPlayer *player;

};
#endif // WIDGET_H
