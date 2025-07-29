#include"WindowManager.h"

//这边将其放进一个数组中
WindowManager::WindowManager(){
    windows.append(LoginWindow::GetLoginWindow());
    windows.append(RegisterWindow::GetRegisterWindow());
    windows.append(Widget::GetMainWindow());

    //登录widget绑定的connect
    connect(LoginWindow::GetLoginWindow(), &LoginWindow::DisplayRegisterWindow,
            this, &WindowManager::DisplayLoginWindow);
    connect(LoginWindow::GetLoginWindow(),&LoginWindow::DisplayMainWindow,
            this,&WindowManager::DisplayMainWindow);

    //注册widget绑定的connect
    connect(RegisterWindow::GetRegisterWindow(),&RegisterWindow::DisplayLoginWindow,
            this,&WindowManager::DisplayRegisterWindow);

    connect(RegisterWindow::GetRegisterWindow(),&RegisterWindow::DisplayMainWindow,
            this,&WindowManager::DisplayMainWindow);

}

void WindowManager::HideWindows(){
    for(QWidget* page:windows){
        if (page->isVisible())
            page->hide();  // 仅隐藏那些当前显示的页面
    }
}

void WindowManager::DisplayMainWindow(){
    HideWindows();
    Widget::GetMainWindow()->show();
}

void WindowManager::DisplayLoginWindow(){
    HideWindows();
    LoginWindow::GetLoginWindow()->show();
}

void WindowManager::DisplayRegisterWindow(){
    HideWindows();
    RegisterWindow::GetRegisterWindow()->show();
}
