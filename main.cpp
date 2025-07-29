#include "widget.h"
#include"window/LoginWindow/loginwindow.h"
#include"window/Register/registerwindow.h"
#include"window/WindowManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowManager window_manager;
    window_manager.DisplayLoginWindow();
    return a.exec();
}
