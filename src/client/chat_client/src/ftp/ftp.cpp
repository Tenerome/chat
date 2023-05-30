#include "ftp.h"
#include <QStandardPaths>
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
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    QNetworkReply* reply=manager.get(request);
    QEventLoop eventloop;//loop event until the reply finished
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();
    //finish reply
    if(reply->error()==QNetworkReply::NoError){
    //save file to local path
        QFile localpath(QStandardPaths::locate(QStandardPaths::DownloadLocation,"",QStandardPaths::LocateDirectory) +ftpurl.mid(5));
        localpath.open(QIODevice::WriteOnly);
        localpath.write(reply->readAll());
        localpath.close();
    }else{
        qDebug()<<"download ftp error:"<<reply->errorString();
    }
}

//if file exist in ftp server,return filename,
//else upload the file and return filename
//or else upload error,return ""
QString FtpClient::upLoad(QString filepath){
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
    QString namehead=get_file_md5(file);//head
    QFileInfo info(file);
    QString tail=info.suffix();//tail
    file.seek(0);//manual move the file point to head
    QByteArray data=file.readAll();//data
    file.close();

    QString fpath="/pub/"+namehead+"."+tail;

    QNetworkAccessManager manager;
    QNetworkRequest request;
    QUrl tempurl=url;
    tempurl.setPath(fpath);
    request.setUrl(tempurl);
    //check file existed?
    QNetworkReply* reply=manager.get(request);
    QEventLoop eventloop;
    QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();
    if(reply->error()==QNetworkReply::NoError){
        return fpath;
    }else{
        reply=manager.put(request,data);
        QObject::connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
        eventloop.exec();
        if(reply->error()==QNetworkReply::NoError){
            return fpath;
        }else{
            qDebug()<<"upload ftp error:"<<reply->errorString();
            return "";
        }
    }
}
QString FtpClient::get_file_md5(QFile &ifs){
    //use reference ,cause QFile object doesn't
    //have copy and move constructors
    QCryptographicHash hash(QCryptographicHash::Md5);
    const qint64 bufferSize = 1024 * 1024;
    QByteArray buffer(bufferSize, '\0');
    while (!ifs.atEnd()) {
        const qint64 bytesRead = ifs.read(buffer.data(), bufferSize);
        if (bytesRead > 0) {
            hash.addData(buffer.data(), bytesRead);
        }
    }
    const QByteArray result = hash.result();
    return QString(result.toHex());
}

