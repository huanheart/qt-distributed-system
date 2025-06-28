


#include"utils.h"


bool Util::isMusicFile(QString file){
    static const QSet<QString> musicExtensions = {
        "mp3", "wav", "flac", "aac", "ogg", "m4a", "alac", "ape", "wma", "opus", "amr", "aiff"
    };

    QFileInfo fileInfo(file);
    QString suffix = fileInfo.suffix().toLower(); // 获取后缀并转小写
    return musicExtensions.contains(suffix);
}
