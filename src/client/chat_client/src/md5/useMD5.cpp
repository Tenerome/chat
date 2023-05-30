#include"useMD5.h"
#include"md5.h"
useMD5::useMD5(QObject *parent):QObject(parent){
}
QString useMD5::toStr(QString message){
    std::string msg=message.toStdString();
    QString ret=MD5(msg).toStr().c_str();
    return ret;
}
