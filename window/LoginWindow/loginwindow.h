#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

#include"../../requestSender/userrequestsender.h"
#include"../../requestSender/musicrequestsender.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
private:
    explicit LoginWindow(QWidget *parent = nullptr);
public:
    ~LoginWindow();
    static LoginWindow* GetLoginWindow() {
        static LoginWindow instance;
        return &instance;
    }

signals:
    //从登录界面跳转到注册界面
    void DisplayRegisterWindow();
    //从登录界面跳转到主界面
    void DisplayMainWindow();
public:
    void DealLogin(bool ok,QString message);

private:
    userRequestSender* user_sender=nullptr;

private slots:

    void on_Login_clicked();

    void on_ToRegister_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
