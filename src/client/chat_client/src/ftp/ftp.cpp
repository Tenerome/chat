#include "ftp.h"


FtpClient::FtpClient(QObject *parent) : QObject(parent){
    url.setScheme("ftp");
    url.setUserName("anonymous");
    url.setPassword("");
    url.setHost("127.0.0.1");
    url.setPort(21);
}

FtpClient::FtpClient(QString scheme,QString host,int port,QString username,QString password,QObject *parent) : QObject(parent){
    url.setScheme(scheme);
    url.setHost(host);
    url.setPort(port);
    url.setUserName(username);
    url.setPassword(password);
}

void FtpClient::downLoad(QString ftpurl){
    printf("get in down ftp\n");
    url.setPath(ftpurl);
    QNetworkRequest request(url);
    QNetworkReply* reply=manager.get(request);
    QEventLoop eventloop;//loop event until the reply finished
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();
    //finish reply
    if(reply->error()==QNetworkReply::NoError){
    //save file to local path
        QFile localpath("./test.jpg");
        localpath.open(QIODevice::WriteOnly);
        localpath.write(reply->readAll());
        localpath.close();
    }else{
        qDebug()<<"download ftp error:"<<reply->errorString();
    }
}

void FtpClient::upLoad(QString filepath){
    url.setPath("/pub/test/test.jpg");
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();

    QNetworkRequest request(url);
    QNetworkReply* reply=manager.put(request,data);
    QEventLoop eventloop;//loop event until the reply finished
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();
    if(reply->error()!=QNetworkReply::NoError){
        qDebug()<<"upload ftp error:"<<reply->errorString();
    }
}

