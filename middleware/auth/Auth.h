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


class InformationManager{

public:
    static InformationManager* GetInstance() {
        static InformationManager instance;
        return &instance;
    }
    void setUserId(int user_id);
    int GetUserId();

    void setFileID(QString file_id);
    QString GetFileID();

    void setHttpFilePath(QString http_file_path);
    QString GetHttpFilePath();

private:
    int user_id;
    QString file_id;
    QString http_file_path;

};


#endif
