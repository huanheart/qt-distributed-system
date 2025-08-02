#ifndef CONTROLTABWIDGET_H
#define CONTROLTABWIDGET_H

#include <QWidget>

namespace Ui {
class controlTabWidget;
}

class controlTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit controlTabWidget(QWidget *parent = nullptr);
    ~controlTabWidget();


    void GetMusicInfos();
signals:
    void sendGetMusicInfos();

private:
    void init();
private:

    Ui::controlTabWidget *ui;
};

#endif // CONTROLTABWIDGET_H
