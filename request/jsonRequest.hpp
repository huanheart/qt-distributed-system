#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include<QMap>

#include<QVariant>
#include<QString>


using namespace std;

class JsonRequest{

public:
    virtual QMap<QString,QVariant> toMap() const=0;

private:

};




#endif
