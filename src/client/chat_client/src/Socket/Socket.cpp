#include "Socket.h"

Client::Client(QObject *parent):QObject(parent){
    client_scoket=new QTcpSocket;
}
bool Client::connect(QString ip, quint16 port){
    client_scoket->connectToHost(ip,port,QTcpSocket::ReadWrite);
    if(client_scoket->waitForConnected(1000)){//wait time
        return true;
    }else{
        return false;
    }
}
bool Client::sendMessage(QString sendstr){
    if(client_scoket->write(sendstr.toLatin1().data(),strlen(sendstr.toLatin1().data()))){
        return true;
    }else{
        return false;
    }
}
QString Client::recvMessage(){
    return client_scoket->readAll();
}
Client::~Client(){
    if(client_scoket->isOpen()){
        client_scoket->disconnectFromHost();
    }
    delete client_scoket;
}
