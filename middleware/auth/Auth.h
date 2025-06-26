#ifndef AUTH_H
#define AUTH_H

#include<QString>

class AuthManager {
public:
    static AuthManager* GetInstance() {
        static AuthManager instance;
        return &instance;
    }

    void setToken(const QString& t);
    QString getToken() const;

private:
    AuthManager()=default;
    QString token;
};


#endif
