#ifndef HOTMUSIC_H
#define HOTMUSIC_H

#include "../jsonRequest.hpp"


class HotMusicRequest : public JsonRequest{

public:
    HotMusicRequest()=default;

    QMap<QString,QVariant> toMap() const override;
    void setRequest();
private:

};





#endif


