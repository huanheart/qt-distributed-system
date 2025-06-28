

#include"Auth.h"


void AuthManager::setToken(const QString& t){
    token = t;
}
QString AuthManager::getToken() const {
    return token;
}


void InformationManager::setUserId(int user_id){
    this->user_id=user_id;
}

int InformationManager::GetUserId(){
    return user_id;
}

void InformationManager::setFileID(QString file_id){
    this->file_id=file_id;
}

QString InformationManager::GetFileID(){
    return file_id;
}


void InformationManager::setHttpFilePath(QString http_file_path){
    this->http_file_path=http_file_path;
}

QString InformationManager::GetHttpFilePath(){
    return "http://"+this->http_file_path;
}


