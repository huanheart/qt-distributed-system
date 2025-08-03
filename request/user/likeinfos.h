#ifndef LIKEINFOS_H
#define LIKEINFOS_H

#include"../jsonRequest.hpp"



class UserLikeInfosRequest : public JsonRequest{

public:
    UserLikeInfosRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QStringList file_ids);
private:
    QStringList file_ids;
};




#endif
