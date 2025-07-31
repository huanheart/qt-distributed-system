
#include"musicInfos.h"

QMap<QString,QVariant> MusicInfosRequest::toMap() const{
    return {
        {"id", id},
        {"cnt",cnt}
    };
}

void MusicInfosRequest::setRequest(int id,int cnt){
    this->id=id;
    this->cnt=cnt;
}
