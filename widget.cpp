#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

void Widget::init(){
    ui->username->setPlaceholderText("请输入账号/邮箱");
    ui->password->setPlaceholderText("请输入密码");
    ui->cap->setPlaceholderText("请输入验证码");
    ui->file_id->setPlaceholderText("请输入指定的file_id");
    user_sender=new userRequestSender(this);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_login_clicked()
{
    user_sender->sendLogin(ui->username->text(),ui->password->text());
}


void Widget::on_register_2_clicked()
{
    user_sender->sendRegister(ui->username->text(),ui->password->text(),ui->cap->text());
}



void Widget::on_captcha_clicked()
{
    user_sender->sendCaptcha(ui->username->text());
}

void Widget::on_download_clicked()
{

}


void Widget::on_upload_clicked()
{

}

