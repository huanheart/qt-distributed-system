#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

#include"../../requestSender/userrequestsender.h"
#include"../../requestSender/musicrequestsender.h"


namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

private:
    explicit RegisterWindow(QWidget *parent = nullptr);

public:
    ~RegisterWindow();

    static RegisterWindow* GetRegisterWindow() {
        static RegisterWindow instance;
        return &instance;
    }

private:
    userRequestSender* user_sender=nullptr;

signals:
    //从注册界面跳转到登录界面
    void DisplayLoginWindow();
    //从注册界面跳转到主界面
    void DisplayMainWindow();
public:
    void DealCaptcha(bool ok,QString message);

    void DealRegister(bool ok,QString message);



private slots:
    void on_ToLogin_clicked();

    void on_captcha_clicked();

    void on_Register_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
