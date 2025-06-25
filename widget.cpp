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
