#ifndef MUSICREQUEST_H
#define MUSICREQUEST_H

#include "jsonRequest.hpp"

class MusicRequest : public JsonRequest{

public:
    MusicRequest(){

    }
    QMap<QString,QVariant> toMap() const override;
private:

};

//todo:待封装
QMap<QString,QVariant> MusicRequest::toMap() const{
    return {

    };
}



#endif
