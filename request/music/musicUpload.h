#ifndef MUSICUPLOAD_H
#define MUSICUPLOAD_H

#include "../jsonRequest.hpp"


class MusicUploadRequest : public JsonRequest{

public:
    MusicUploadRequest(){

    }
    QMap<QString,QVariant> toMap() const override;
private:

};

//todo:待封装
QMap<QString,QVariant> MusicUploadRequest::toMap() const{
    return {

    };
}


#endif


