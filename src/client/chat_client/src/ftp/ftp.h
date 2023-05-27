#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>
#include <QNetworkReply>
#include <QDebug>

class FtpClient : public QObject{
    Q_OBJECT
public:
    explicit FtpClient(QObject *parent = nullptr);


signals:

public slots:
    void DownloadFtp(QString ftpurl);
    void UploadFtp(QString path);

private slots:
    void replyFinished(QNetworkReply*);
    void on_Readready();

private:
    QNetworkAccessManager *myNetworkManager;
    QNetworkRequest myNetworkRequest;
    QNetworkReply *myNetworkReply;
    QFile *downloadedFile;
};

#endif // FTPCLIENT_H
