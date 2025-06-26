#ifndef MUSICUPLOAD_H
#define MUSICUPLOAD_H

#include "../formDataRequest.hpp"



class MusicUploadRequest : public FormDataRequest{

public:
    MusicUploadRequest()=default;

    //由于上传服务，不需要传其他字段，固然这边直接返回一个空map即可
    QMap<QString,QVariant> toMap() const override;
    void setRequest();
public:

public:


};





#endif


