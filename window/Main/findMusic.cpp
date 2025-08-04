#include "findMusic.h"
#include "ui_findMusic.h"

findMusic::findMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findMusic)
{
    id=0;
    ui->setupUi(this);
    music_sender=new musicRequestSender(this);
    user_sender=new userRequestSender(this);

    player=new MusicPlayer(this);
    connect(music_sender,&musicRequestSender::sendGetMusicInfosInformation,this,findMusic::DealFindMusic);

    //注意：这个依旧是发现音乐里面的功能，因为发现音乐里面有下载功能
    //但是下载页面的需求可能有用到发现音乐所维护的这个map表(也不一定，因为维护了文件，只用读取文件信息即可）
    connect(music_sender,&musicRequestSender::sendMusicDownloadInformation,this,findMusic::DealDownLoadMusic);

    connect(user_sender,&userRequestSender::sendQueryLikeInfosInformation,this,findMusic::DealLikeInfos);

    connect(user_sender,&userRequestSender::sendLikeInformation,this,findMusic::DealLike);

}

void findMusic::sendGetMusicInfos(){
    //构造函数初始化的时候需要调用这个 :todo:更改成点击发现音乐的时候再发送请求？
    //    （不行，因为这样重复点击发送音乐会重复请求）固然要做对应特殊操作，但是不如直接发送
    music_sender->sendGetMusicInfos(id,cnt);
    //todo：然后发送那个请求，将当前拥有的uuid传输过去，服务端查询当前user_id有哪些uuid是当前用户点赞的
    //todo：将对应的渲染组件的部分和处理的部分拆开，组件最后维护
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

    emit setMusicPathToWatcher(save_path+musicObj["music_name"].toString()+"."+ QFileInfo(musicObj["file_path"].toString()).suffix());
    if(Item_map.find(file_id)!=Item_map.end()){
        NewCourierItem* nitem=Item_map[file_id];
        nitem->setFinishedDownloadStatus();
        nitem->display();
    }

}

void findMusic::DealLike(bool ok,QString message,QString file_id,qint64 LikeCnt,qint64 LikeStatus){
    if(!ok){
        //这里后续还应该加载一个错误的界面上去
        qDebug()<<"DealLike error: "<<message;
        return ;
    }
    qDebug()<<"当前file_id进行回调: "<<file_id;
    //todo:将对应file_id的点赞按钮进行更改，点赞数
    if(Item_map.find(file_id)!=Item_map.end()){
        NewCourierItem* nitem=Item_map[file_id];
        if(LikeStatus==1){
            //从服务端获取的状态为已点赞
            nitem->setFinishedLikeStatus();
        }else {
            //从服务端获取的状态为未点赞
            nitem->setLikeStatus();
        }
        nitem->setMusicLikeCount(LikeCnt);
        //切记更新状态后需要刷新
        nitem->display();
    }
}

void findMusic::DealLikeInfos(bool ok,QString message,QStringList file_ids){
    if(!ok){
        //这里后续还应该加载一个错误的界面上去
        qDebug()<<"DealLikeInfos error: "<<message;
        return ;
    }
    qDebug()<<"DealLikeInfos enter! ";
    for (int i = 0; i < file_ids.size(); i++) {

        QString file_id = file_ids[i];
        qDebug()<<"test file_id is: "<<file_id;
        if(Item_map.find(file_id)!=Item_map.end()){
            //将对应点赞按钮的状态更新为已点赞
            NewCourierItem* nitem=Item_map[file_id];
            nitem->setFinishedLikeStatus();
            //一定要进行display操作，之前就是忘记还以为哪里出错了
            nitem->display();
        }

    }
}
//findmusic将指定uuid对应的item的已下载变成下载，恢复下载按钮
void findMusic::onFileDeleteChanged(const QString &path){
    QFileInfo fileInfo(path);
    qDebug()<<"findMusic onFileChanged is "<<path;
    //只对删除做操作（更改名字这些暂且不管)
    if (fileInfo.exists()) {
        return ;
    }
    qDebug()<<"findMusic onFileChanged is "<<path;
    QString baseName = fileInfo.baseName();
    if(Item_map.find(baseName)!=Item_map.end()){
        NewCourierItem* nitem=Item_map[baseName];
        nitem->setDownloadStatus();
        nitem->display();
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
        file_ids.append(uuid);
        if(id< _id)
            id=_id;
    }
    //2：将获取到的musicListArray数据更新到ui上
    AddItem();
    //3：遍历file_infos文件，读取每一个uuid
    ChangeItemDownloadStatus();
    //4：获取当前状态的map中哪些file_id是被当前用户给点赞了的（更新ui）
    user_sender->queryLikeInfos(file_ids);
}

void findMusic::ChangeItemDownloadStatus(){
    QStringList uuidList=ReadDownloadStatus(file_info);
    //然后将其指定的uuid的item进行渲染
    for(int i=0;i<uuidList.size();i++){
        Item_map[uuidList[i] ]->setFinishedDownloadStatus();
        Item_map[uuidList[i] ]->display();
    }
}

QStringList findMusic::ReadDownloadStatus(const QString &filePath){
    QStringList uuidList;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("无法打开文件: %s", qUtf8Printable(filePath));
        return uuidList;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isArray()) {
        qWarning("JSON 解析失败或格式不是数组");
        return uuidList;
    }
    QJsonArray array = doc.array();
    for (const QJsonValue &value : array) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            if (obj.contains("uuid") && obj["uuid"].isString()) {
                uuidList.append(obj["uuid"].toString());
            }
        }
    }
    return uuidList;
}

void findMusic::AddItem(){
    for (const auto &key : music_map.keys()) {
        QJsonObject musicObj = music_map.value(key);
        qint64 _id = musicObj["id"].toVariant().toLongLong();
//        QString uuid = musicObj["uuid"].toString();  key就是uuid
        qint64 like_count=musicObj["like_count"].toVariant().toLongLong();
        qDebug()<<"like count is "<<like_count;
        QString music_name=musicObj["music_name"].toString();
        qint64 file_size=musicObj["file_size"].toVariant().toLongLong();
        double duration=musicObj["duration"].toDouble();
        QString filePath = musicObj["file_path"].toString();
        qint64 userId = musicObj["user_id"].toVariant().toLongLong();
        // 创建 item 和 widget
        QListWidgetItem *item = new QListWidgetItem(ui->listAll);
        NewCourierItem *nitem = new NewCourierItem();
        //保存进去方便维护
        Item_map[key]=nitem;
        // 设置数据
        nitem->setNum(_id);
        nitem->setMusicName(music_name);
        nitem->setMusicLikeCount(like_count);
        nitem->setMusicTimer(duration);
        nitem->setUserID(userId);
        nitem->setFileSize(file_size);
        nitem->setFileID(key);
        nitem->setFilePath(filePath);

        nitem->setPicture(":/images/NewMusic/01.png");
        //nitem->setFilePath("D:\\qt_wen_jian_mu_lu\\MyMusicPlatform\\images\\NewMusic\\01.png");
        //最后一步将内容显示到item上
        nitem->display();
        // 添加调试颜色（确认能显示）
        nitem->setStyleSheet("background-color: rgba(255, 0, 0, 50);");  // 浅红色方便观察

        // 绑定按钮信号
        //下载
        connect(nitem, &NewCourierItem::download, this, [=](QString file_id) {
            music_sender->sendMusicDownload(file_id, save_path);
        });
        //播放音乐
        connect(nitem, &NewCourierItem::playMusic, this, [=](QString file_id) {
            player->setFileId(file_id);
            player->startPlay();
        });
        //点赞/取消点赞
        connect(nitem,&NewCourierItem::Like,this,[=](QString file_id){
            user_sender->sendLike(file_id);
            //注意：后续需要拦截该内部发送的信号，将nitem中的点赞数，以及按钮状态更新
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
