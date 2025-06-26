#ifndef MUSICUPLOAD_H
#define MUSICUPLOAD_H

#include "../formDataRequest.hpp"


class MusicUploadRequest : public FormDataRequest{

public:
    MusicUploadRequest()=default;

    QMap<QString,QVariant> toMap() const override;

public:
    //存放对应的指定文件路径

private:
    //存放指定字段，但是上传


};

//todo:待封装
QMap<QString,QVariant> MusicUploadRequest::toMap() const{
    return {

    };
}


#endif


