#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    user_sender=new userRequestSender(this);

    connect(user_sender,&userRequestSender::sendLoginInformation,this,LoginWindow::DealLogin);
    ui->username->setPlaceholderText("请输入账号/邮箱");
    ui->passwd->setPlaceholderText("请输入密码");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::DealLogin(bool ok,QString message){
    if(!ok){
        QMessageBox::critical(this, "失败", message);
        return ;
    }
    QMessageBox::information(this, "成功", message);
    //跳转到主界面
    //todo：后续可能还要发送网络请求去获取头像等数据
    emit DisplayMainWindow();
}

void LoginWindow::on_Login_clicked()
{
    user_sender->sendLogin(ui->username->text(),ui->passwd->text());

}

void LoginWindow::on_ToRegister_clicked()
{
    emit DisplayRegisterWindow();
}

