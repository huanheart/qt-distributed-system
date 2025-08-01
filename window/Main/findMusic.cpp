#include "findMusic.h"
#include "ui_findMusic.h"

findMusic::findMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findMusic)
{
    id=0;
    ui->setupUi(this);
    music_sender=new musicRequestSender(this);
    player=new MusicPlayer(this);
    connect(music_sender,&musicRequestSender::sendGetMusicInfosInformation,this,findMusic::DealFindMusic);

    //注意：这个依旧是发现音乐里面的功能，因为发现音乐里面有下载功能
    //但是下载页面的需求可能有用到发现音乐所维护的这个map表(也不一定，因为维护了文件，只用读取文件信息即可）
    connect(music_sender,&musicRequestSender::sendMusicDownloadInformation,this,findMusic::DealDownLoadMusic);

}

void findMusic::sendGetMusicInfos(){
    //构造函数初始化的时候需要调用这个 :todo:更改成点击发现音乐的时候再发送请求？
    //    （不行，因为这样重复点击发送音乐会重复请求）固然要做对应特殊操作，但是不如直接发送
    music_sender->sendGetMusicInfos(id,cnt);
}

void findMusic::DealDownLoadMusic(bool ok,QString message,QString file_id){
    if(!ok){
        QMessageBox::information(this,"下载音乐失败",message);
        return ;
    }
    //下载音乐成功
    //1：需要将当前音乐的map[uuid]的相应信息给追加到指定文件中，方便为下载页面读取本地文件信息
    //(注意：这里的uuid是需要提前知道的，所以不太好处理，因为响应是没有uuid的，我们并不知道下载的是哪个文件
    //（已解决）发送下载请求的时候既然会传递一个file_id，那么回调的时候也将这个file_id回调出来即可

    QJsonObject musicObj=music_map[file_id];
    //将下面的数据放入到文件中，方便下载管理页面进行一个获取(注释的内容是暂且不需要的）
//        qint64 id = musicObj["id"].toVariant().toLongLong();
    //    QString filePath = musicObj["file_path"].toString();
    //    qint64 userId = musicObj["user_id"].toVariant().toLongLong();
    // 1. 准备一个新的对象
    QJsonObject newObj;
    newObj["uuid"] = musicObj["uuid"].toString();
    //这里方便获取后缀，方便下载管理中进行播放音乐
    newObj["music_name"] = musicObj["music_name"].toString()+"."+ QFileInfo(musicObj["file_path"].toString()).suffix();
    newObj["like_count"] = musicObj["like_count"].toVariant().toLongLong();
    newObj["file_size"] = musicObj["file_size"].toVariant().toLongLong();
    newObj["duration"] = musicObj["duration"].toDouble();

    // 2. 读取原有数组（如果文件存在）
    QJsonArray jsonArray;

    QFile file(file_info);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray data = file.readAll();
            file.close();

            QJsonParseError parseError;
            QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
            if (parseError.error == QJsonParseError::NoError && doc.isArray()) {
                jsonArray = doc.array(); // 读取原数组
            }
        }
    }

    // 3. 添加新对象
    jsonArray.append(newObj);

    // 4. 写回文件
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QJsonDocument newDoc(jsonArray);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << newDoc.toJson(QJsonDocument::Indented); // 美化输出
        file.close();
    } else {
        qWarning("无法打开文件写入");
    }

}

void findMusic::DealFindMusic(bool ok,QString message,QJsonArray musicListArray){
    if(!ok){
        //这里后续还应该加载一个错误的界面上去
        qDebug()<<"DealFindMusic error: "<<message;
        return ;
    }
    ui->listAll->clear();

    //1：将对应的数据存放到map中，并更新max_id
    //todo：下次请求的时候就是传递这个max_id了(需要在往下拉页面的时候再请求）
    for (const QJsonValue &value : musicListArray) {
        QJsonObject musicObj = value.toObject();

        qint64 _id = musicObj["id"].toVariant().toLongLong();
        QString uuid = musicObj["uuid"].toString();

        music_map[uuid]=musicObj;
        if(id<_id)
            id=_id;
        //2：将获取到的musicListArray数据更新到ui上
        qint64 like_count=musicObj["like_count"].toVariant().toLongLong();
        QString music_name=musicObj["music_name"].toString();
        qint64 file_size=musicObj["file_size"].toVariant().toLongLong();
        double duration=musicObj["duration"].toDouble();
        QString filePath = musicObj["file_path"].toString();
        qint64 userId = musicObj["user_id"].toVariant().toLongLong();



        // 创建 item 和 widget
        QListWidgetItem *item = new QListWidgetItem(ui->listAll);
        NewCourierItem *nitem = new NewCourierItem(); // 保证 .ui 里控件都 setupUi 了

        // 设置数据
        nitem->setNum(id);
        nitem->setMusicName(music_name);
        nitem->setMusicLikeCount(like_count);
        nitem->setMusicTimer(duration);
        nitem->setUserID(userId);
        nitem->setFileSize(file_size);
        nitem->setFileID(uuid);
        nitem->setFilePath(filePath);

        nitem->setPicture(":/images/NewMusic/01.png");

//        nitem->setFilePath("D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\images\\NewMusic\\01.png");
        //最后一步将内容显示到item上
        nitem->display();
        // 添加调试颜色（确认能显示）
        nitem->setStyleSheet("background-color: rgba(255, 0, 0, 50);");  // 浅红色方便观察

        // 绑定按钮信号
        connect(nitem, &NewCourierItem::download, this, [=](QString file_id) {
            music_sender->sendMusicDownload(file_id, save_path);
        });
        connect(nitem, &NewCourierItem::playMusic, this, [=](QString file_id) {
            player->setFileId(file_id);
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


findMusic::~findMusic()
{
    delete ui;
}
