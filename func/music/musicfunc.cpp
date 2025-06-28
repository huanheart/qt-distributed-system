#include "musicfunc.h"


void MusicFunc::setMusicParent(QObject *parent){
    parentWidget=qobject_cast<QWidget *>(parent);
}


void MusicFunc::downloadFile(const QUrl &fileUrl, const QString &file_name,const QString &saveDir) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(parentWidget);
    QNetworkRequest request(fileUrl);
    QNetworkReply *reply = manager->get(request);

    // 自动获取文件扩展名
    QString suffix = QFileInfo(fileUrl.path()).suffix();

    if (suffix.isEmpty()) suffix = "mp3"; // 默认后缀

    QString savePath = saveDir + file_name+"." + suffix;
    QFile *file = new QFile(savePath);

    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::warning(parentWidget, "错误", "无法打开文件路径进行保存！");
        delete file;
        manager->deleteLater();
        return;
    }

    // 写入数据
    QObject::connect(reply, &QNetworkReply::readyRead, parentWidget, [=]() {
        file->write(reply->readAll());
    });

    QObject::connect(reply, &QNetworkReply::finished, parentWidget, [=]() {
        file->flush();
        file->close();
        file->deleteLater();

        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "下载成功：" << savePath;
            QMessageBox::information(parentWidget, "下载完成", "视频下载成功！");
        } else {
            qDebug() << "下载失败：" << reply->errorString();
            QMessageBox::warning(parentWidget, "下载失败", reply->errorString());
            QFile::remove(savePath);
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}
