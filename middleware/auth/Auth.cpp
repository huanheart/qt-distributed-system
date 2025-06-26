

#include"Auth.h"


void AuthManager::setToken(const QString& t){
    token = t;
}
QString AuthManager::getToken() const {
    return token;
}
