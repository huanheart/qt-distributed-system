#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QWidget>
#include<QVector>

#include"window/LoginWindow/loginwindow.h"
#include"window/Register/registerwindow.h"
#include"../widget.h"


class WindowManager : public QWidget
{
    Q_OBJECT
public:
    WindowManager();
    //展示登录界面
    void DisplayLoginWindow();
    //展示注册界面
    void DisplayRegisterWindow();

private:
    //隐藏所有界面
    void HideWindows();

private:
    QVector<QWidget*> windows;
    QWidget* main_widget;

signals:

};


#endif
