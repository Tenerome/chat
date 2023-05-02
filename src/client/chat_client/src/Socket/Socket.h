#ifndef SOCKET_H
#define SOCKET_H
#include <QObject>
#include <QTcpSocket>

class Client:public QObject{
  Q_OBJECT
private:
    QTcpSocket *client_socket;
public:
    explicit Client(QObject *parent=nullptr);
    ~Client();
    Q_INVOKABLE bool connect(QString ip,quint16 port);
    Q_INVOKABLE bool sendMessage(QString sendstr);
    Q_INVOKABLE QString recvMessage();
    Q_INVOKABLE bool getConnectStatus();

};
#endif // SOCKET_H
