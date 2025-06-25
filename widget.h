#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include<QLine>
#include<QPushButton>
#include<QMessageBox>


#include"request/userRequest.hpp"
#include"requestSender/jsonRequestSender.h"
#include"request/musicRequest.hpp"

#include"router/userRouter.h"
#include"router/musicRouter.h"

#include"router/router.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    void init();

private:
    JsonRequestSender* sender;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_login_clicked();

    void on_register_2_clicked();


    void on_captcha_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
