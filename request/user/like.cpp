
#include "like.h"

QMap<QString,QVariant> UserLikeRequest::toMap() const{
    return {
        {"file_id", file_id}
    };
}

void UserLikeRequest::setRequest(QString file_id){
    this->file_id=file_id;
}



