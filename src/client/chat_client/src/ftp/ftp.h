#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>
#include <QNetworkReply>
#include <qeventloop.h>
#include <QDebug>
#include <QCryptographicHash>


class FtpClient : public QObject{
    Q_OBJECT
public:
    //default constructor with ftp://localhost :anonymous
    explicit FtpClient(QObject *parent = nullptr);
    explicit FtpClient(QString scheme,QString host,int port,QString username,QString password,QObject *parent = nullptr);
    Q_INVOKABLE void downLoad(QString ftpurl);
    Q_INVOKABLE QString upLoad(QString filepath);
    QString get_file_md5(QFile &ifs);

private:
    QUrl url;
};

#endif // FTPCLIENT_H
