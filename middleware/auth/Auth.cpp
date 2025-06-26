

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
