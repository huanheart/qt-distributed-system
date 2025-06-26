#ifndef FORMDATAREQUEST_H
#define FORMDATAREQUEST_H

#include<QMap>

#include<QVariant>
#include<QString>


using namespace std;

class FormDataRequest{

public:
    virtual QMap<QString,QVariant> toMap() const=0;

private:

};




#endif
