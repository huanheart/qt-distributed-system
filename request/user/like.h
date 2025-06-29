#ifndef LIKE_H
#define LIKE_H

#include"../jsonRequest.hpp"

class UserLikeRequest : public JsonRequest{

public:
    UserLikeRequest()=default;

    QMap<QString,QVariant> toMap() const override;

    void setRequest(QString file_id);
private:
    QString file_id;
};




#endif
