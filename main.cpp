#include "widget.h"
#include"window/LoginWindow/loginwindow.h"
#include"window/Register/registerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();
//    LoginWindow login_window;
//    login_window.show();

    RegisterWindow register_window;
    register_window.show();

    return a.exec();
}
