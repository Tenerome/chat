#ifndef SOCKET_H
#define SOCKET_H
#include <QObject>
#include <QTcpSocket>

class Client:public QObject{
  Q_OBJECT
public:
    explicit Client(QObject *parent=nullptr);
    ~Client();
    Q_INVOKABLE bool connect(QString ip,quint16 port);
    Q_INVOKABLE bool sendMessage(QString sendstr);
    Q_INVOKABLE QString recvMessage();
    Q_INVOKABLE bool getConnectStatus();//TODEL

signals:

public slots:

private:
    QTcpSocket *client_scoket;
};
#endif // SOCKET_H
