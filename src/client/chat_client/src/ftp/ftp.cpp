#include "ftp.h"

FtpClient::FtpClient(QObject *parent) : QObject(parent){
    myNetworkManager = new QNetworkAccessManager(this);
    connect( myNetworkManager,SIGNAL(finished(QNetworkReply*)), this,SLOT(replyFinished(QNetworkReply*)));
}


void FtpClient::DownloadFtp(QString ftpurl){
    QDate date;
    QString imagepath=date.toString("yyyy-mm-dd-hh-mm");
    downloadedFile = new QFile("F:/FtpClient/1.png");
    downloadedFile->open(QIODevice::WriteOnly);
    QUrl url(ftpurl);
    url.setPort(21);//设置端口
    url.setUserName("anonymous");//设置ftp用户名
    url.setPassword("");//设置密码
    qDebug()<<url;
    myNetworkRequest.setUrl(url);
    myNetworkReply = myNetworkManager->get(myNetworkRequest);
    connect(myNetworkReply,SIGNAL(readyRead()),this,SLOT(on_Readready()));
}

void FtpClient::UploadFtp(QString path){
    downloadedFile = new QFile(path);
    downloadedFile->open(QIODevice::ReadOnly);
    QByteArray byte_file = downloadedFile->readAll();
    QUrl url("ftp://127.0.0.1/ASDASD.png");
    url.setPort(21);//设置端口
    url.setUserName("anonymous");//设置ftp用户名
    url.setPassword("");//设置密码
    qDebug()<<url;
    myNetworkRequest.setUrl(url);
    myNetworkManager->put(myNetworkRequest,byte_file);
}

void FtpClient::replyFinished(QNetworkReply *reply){
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() <<__FILE__<<__LINE__;
    if(reply->error() == QNetworkReply::NoError)
    {
        downloadedFile->close();
    }else{
        qDebug()<<__FUNCTION__<<reply->errorString()<<__FILE__<<__LINE__;
    }
    reply->deleteLater();
}

void FtpClient::on_Readready(){
    downloadedFile->write(myNetworkReply->readAll());
}

