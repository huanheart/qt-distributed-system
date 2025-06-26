
#include"musicDownload.h"

//todo:待封装
QMap<QString,QVariant> MusicDownloadRequest::toMap() const{
    return {
        {"file_id", file_id}
    };
}

void MusicDownloadRequest::setRequest(QString file_id){
    this->file_id=file_id;
}
