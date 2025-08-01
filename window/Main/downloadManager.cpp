#include "downloadManager.h"
#include "ui_downloadManager.h"

DownloadManager::DownloadManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadManager)
{
    ui->setupUi(this);
    LoadFileInfo();

}

void DownloadManager::LoadFileInfo() {

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
    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString uuid = obj["uuid"].toString();
            if (!uuid.isEmpty()) {
                music_map.insert(uuid, obj);
            } else {
                qWarning("某个对象缺失 uuid 字段，跳过");
            }
        }
    }

    // 如果你希望将 music_map 保存为成员变量，则：
    this->music_map = music_map; // 假设你类中有 QMap<QString, QJsonObject> music_map_;
}

DownloadManager::~DownloadManager()
{
    delete ui;
}
