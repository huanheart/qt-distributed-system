
#ifndef MUSICROUTER_H
#define MUSICROUTER_H

#include<QString>

using namespace std;

class musicRouter{

public:
    static musicRouter* GetInstance(){
        static musicRouter r;
        return &r;
    }

    QString GetMusicUploadPath();
    QString GetMusicDownloadPath();
    QString GetMusicStreamPath();
    QString GetHotMusicPath();
    QString GetMusicInfosPath();
private:
    //顶级目录
    QString music_path="/music";

    QString music_upload_path="/music_upload";

    QString music_download_path="/music_download";

    QString music_stream_path="/stream";

    QString hot_music_path="/rankings";

    QString music_infos="/music_infos";

private:

    musicRouter()=default;
    musicRouter(const musicRouter&)=delete;
    musicRouter& operator=(const musicRouter&) = delete;

};






#endif
