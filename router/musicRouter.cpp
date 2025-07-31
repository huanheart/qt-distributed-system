#include"musicRouter.h"




QString musicRouter::GetMusicUploadPath(){
    return music_path+music_upload_path;
}

// /music/music_download
QString musicRouter::GetMusicDownloadPath(){
    return music_path+music_download_path;
}


QString musicRouter::GetMusicStreamPath(){
    return music_path+music_stream_path;
}


QString musicRouter::GetHotMusicPath(){
    return music_path+hot_music_path;
}

QString musicRouter::GetMusicInfosPath(){
    return music_path+music_infos;
}

