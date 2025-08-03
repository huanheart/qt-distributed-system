#include "downloadManager.h"
#include "ui_downloadManager.h"

DownloadManager::DownloadManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadManager)
{
    ui->setupUi(this);
    player=new MusicPlayer(this);
}

void DownloadManager::LoadFileInfo() {
    //将ui->listwidget上的元素全部删除
    while (ui->listAll->count() > 0) {
        QListWidgetItem *item = ui->listAll->takeItem(0); // 从 list 中取出
        QWidget *widget = ui->listAll->itemWidget(item);  // 获取绑定的自定义 widget
        if (widget) {
            delete widget;  // 删除自定义 widget
        }
        delete item;  // 删除 QListWidgetItem
    }

    QMap<QString, QJsonObject> music_map;

    QFile file(file_info);
    if (!file.exists()) {
        qWarning("file_info.json 文件不存在");
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("无法打开 file_info.json 文件读取");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isArray()) {
        qWarning("file_info.json 格式错误或不是 JSON 数组");
        return;
    }

    QJsonArray jsonArray = doc.array();
    int id=0;
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject musicObj = value.toObject();
            QString uuid = musicObj["uuid"].toString();
            music_map[uuid]=musicObj;
            qint64 like_count=musicObj["like_count"].toVariant().toLongLong();
            QString music_name=musicObj["music_name"].toString();
            //提取前缀
//            music_name=QFileInfo(music_name).completeBaseName();

            qint64 file_size=musicObj["file_size"].toVariant().toLongLong();
            double duration=musicObj["duration"].toDouble();

            //这里不需要路径，find_music的是远程路径，而这里直接播放当地文件即可
//            QString filePath = musicObj["file_path"].toString();

            // 创建 item 和 widget
            QListWidgetItem *item = new QListWidgetItem(ui->listAll);
            NewCourierItem *nitem = new NewCourierItem(); // 保证 .ui 里控件都 setupUi 了

            // 设置数据
            nitem->setNum(id++);
            nitem->setMusicName(music_name);
            nitem->setMusicLikeCount(like_count);
            nitem->setMusicTimer(duration);
            nitem->setFileSize(file_size);
            nitem->setFileID(uuid);
            nitem->setPicture(":/images/NewMusic/01.png");
            //标记为已下载状态
            nitem->setFinishedDownloadStatus();
            //将点赞功能隐藏掉，本地音乐不提供点赞功能
            nitem->HideLike();
            //最后一步将内容显示到item上
            nitem->display();
            // 添加调试颜色（确认能显示）
            nitem->setStyleSheet("background-color: rgba(255, 0, 0, 50);");  // 浅红色方便观察

            // 绑定按钮信号
            connect(nitem, &NewCourierItem::playLocalMusic, this, [=](QString file_path) {
                //todo：这里还要检验文件是否已被删除（此时需要删除file_info文件相关信息)
                //主要用户可能在文件浏览器删除这个文件
                player->setLocalFileId(save_path+file_path);
                qDebug()<<"LocalFileId is:  "<<save_path+file_path;
                qDebug() << "exists:" << QFile::exists(save_path+file_path);
                player->startPlay();
            });
            QSize hint = nitem->sizeHint();
            hint.setHeight(80); // 给一个足够的高度
            item->setSizeHint(hint);
            // 加入 list
            ui->listAll->addItem(item);
            ui->listAll->setItemWidget(item, nitem);
        }
    }
    this->music_map = music_map;
}

DownloadManager::~DownloadManager()
{
    delete ui;
}
