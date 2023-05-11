#include "Socket.h"

Client::Client(QObject *parent):QObject(parent){
    client_socket=new QTcpSocket;
}
bool Client::connect(QString ip, quint16 port){
    client_socket->connectToHost(ip,port,QTcpSocket::ReadWrite);
    if(client_socket->waitForConnected(1000)){//wait time
        return true;
    }else{
        return false;
    }
}
bool Client::sendMessage(QString sendstr){
    if(client_socket->write(sendstr.toStdString().data(),SOCKET_SIZE)){
        return true;
    }else{
        return false;
    }
}
QString Client::recvMessage(){
    return client_socket->readAll();
}
bool Client::getConnectStatus(){
    if(client_socket->state()==QAbstractSocket::UnconnectedState){//TOTEST
        return false;
    }else{
        return true;
    }
}
Client::~Client(){
    if(client_socket->isOpen()){
        client_socket->disconnectFromHost();
    }
    delete client_socket;
}
