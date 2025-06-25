#ifndef MUSICDOWNLOAD_H
#define MUSICDOWNLOAD_H

#include "../jsonRequest.hpp"


class MusicDownloadRequest : public JsonRequest{

public:
    MusicDownloadRequest(){

    }
    QMap<QString,QVariant> toMap() const override;
private:

};

//todo:待封装
QMap<QString,QVariant> MusicDownloadRequest::toMap() const{
    return {

    };
}


#endif


