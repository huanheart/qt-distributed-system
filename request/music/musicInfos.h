#ifndef MUSICINFOS_H
#define MUSICINFOS_H

#include "../jsonRequest.hpp"
class MusicInfosRequest : public JsonRequest{

public:
    MusicInfosRequest()=default;

    QMap<QString,QVariant> toMap() const override;
    void setRequest(int id,int cnt);
private:
    int id;
    int cnt;
};




#endif


