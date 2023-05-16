#include "chat_server.h"
void Send(int socket,const char *buffer){ 
    cout<<"<Send>"<<socket<<"buffer:"<<buffer<<endl;//TODEL
    usleep(150000);
    send(socket,buffer,SOCKET_SIZE,0);
}
int Recv(int socket,string &recv_string){
    usleep(100000);
    char buff[SOCKET_SIZE-1]={'\0'};
    int ret=recv(socket,buff,SOCKET_SIZE,0);
    recv_string=buff;
    return ret;
}
bool get_Password(const char *path,char *out){
    char in[16];
    ifstream(path)>>in;
    if(base64_decode(in,strlen(in),(unsigned char*)out)==0){
        cerr<<"base64 decode failed,maybe you need to run as root or check other configure"<<endl;
        return false;
    }
    out[strlen((char*)out)-1]='\0';//
    return true;
}