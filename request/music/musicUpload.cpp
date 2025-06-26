
#include"musicUpload.h"


//由于上传服务，不需要传其他字段，固然这边直接返回一个空map即可
QMap<QString,QVariant> MusicUploadRequest::toMap() const{
    return {

    };
}


void MusicUploadRequest::setRequest(){

}
