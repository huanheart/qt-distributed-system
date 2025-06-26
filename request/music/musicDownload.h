#ifndef MUSICDOWNLOAD_H
#define MUSICDOWNLOAD_H

#include "../jsonRequest.hpp"


class MusicDownloadRequest : public JsonRequest{

public:
    MusicDownloadRequest()=default;

    QMap<QString,QVariant> toMap() const override;
    void setRequest(QString file_id);
private:
    QString file_id;
};




#endif


