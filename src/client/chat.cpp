#include "client.h"
int main(){
    int server_socket=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port=htons(8888);
    if(connect(server_socket,(sockaddr*)&server_addr,sizeof(server_addr))==0){
        cout<<"chat: main: connected to server socket"<<endl;
    }else{
        cerr<<"chat: main: failed to connect socket"<<endl;
        exit(-1);
    }
    user_Property *user_pro=new user_Property;
    memcpy(user_pro->account,"xuanyi",sizeof("henghua"));
    memcpy(user_pro->password,"666888",sizeof("666888"));
    memcpy(user_pro->name,"张鑫",sizeof("张鑫"));
    char *buff=(char*)malloc(USER_PROPERTY_SIZE);//memset 两个空间大小需相同
    memcpy(buff,user_pro,USER_PROPERTY_SIZE);
    send(server_socket,buff,USER_PROPERTY_SIZE,0);
    delete(user_pro);
    free(buff);
}