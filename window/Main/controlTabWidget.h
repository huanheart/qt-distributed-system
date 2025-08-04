#ifndef CONTROLTABWIDGET_H
#define CONTROLTABWIDGET_H

#include <QWidget>
#include<QFileSystemWatcher>

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

public slots:
    void receiveShowCurrentTab(int cur,int index);

signals:
    void sendGetMusicInfos();

private:
    void init();
private:
    QFileSystemWatcher* watcher;
    Ui::controlTabWidget *ui;
};

#endif // CONTROLTABWIDGET_H
