#include "registerwindow.h"
#include "ui_registerwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    user_sender=new userRequestSender(this);

    connect(user_sender,&userRequestSender::sendCaptchaInformation,this,RegisterWindow::DealCaptcha);

    connect(user_sender,&userRequestSender::sendRegisterInformation,this,RegisterWindow::DealRegister);
    ui->username->setPlaceholderText("请输入账号/邮箱");
    ui->passwd->setPlaceholderText("请输入密码");
    ui->cap->setPlaceholderText("请输入验证码");

}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_ToLogin_clicked()
{
    emit DisplayLoginWindow();
}

//注意，当这里成功调用的时候，还需要进行一个跳转功能，所以参数中可以再设置一个回调函数或者传递一个信号？
void RegisterWindow::on_captcha_clicked()
{
    user_sender->sendCaptcha(ui->username->text());
}


void RegisterWindow::on_Register_clicked()
{
    user_sender->sendRegister(ui->username->text(),ui->passwd->text(),ui->cap->text());
}


void RegisterWindow::DealCaptcha(bool ok,QString message){
    if(!ok){
        QMessageBox::critical(this, "失败", message);
        return ;
    }
    QMessageBox::information(this, "成功", message);
}

void RegisterWindow::DealRegister(bool ok,QString message){
    if(!ok){
        QMessageBox::critical(this, "失败", message);
        return ;
    }
    QMessageBox::information(this, "注册成功", message);
    //跳转到主界面
    //todo：后续可能还要发送网络请求去获取头像等数据
    emit DisplayMainWindow();
}






