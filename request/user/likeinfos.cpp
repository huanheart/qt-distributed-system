
#include "likeinfos.h".h"

QMap<QString,QVariant> UserLikeInfosRequest::toMap() const{
    return {
        {"file_ids", file_ids}
    };
}

void UserLikeInfosRequest::setRequest(QStringList file_ids){
    this->file_ids=file_ids;
}
