#include "chat_server.h"
using std::string;
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

bool mid_Log_UP(DB db,const char *json_string,int session_socket){
    json log_up_json=json::parse(json_string);
    string account=log_up_json["account"];
    string name=log_up_json["name"];
    string password=log_up_json["password"];
    switch(Log_UP(db,account.c_str(),password.c_str(),name.c_str())){
        case SQL_ACCOUNT_REGISTED:
            send(session_socket,"The account has been registed",SOCKET_SIZE,0);
            return false;
        case SQL_FALSE:
            return false;
        case SQL_TRUE:
            send(session_socket,"Log up succeed",SOCKET_SIZE,0);
            return true;
        default:
            cerr<<"chat_server:Log Up Error"<<endl;
            exit(-1);
    }
}

bool mid_Log_IN(DB db,const char *json_string,int session_socket){
    json log_in_json=json::parse(json_string);
    string account=log_in_json["account"];
    string password=log_in_json["password"];
    switch(Log_IN(db,account.c_str(),password.c_str(),"127.0.0.1")){
        case SQL_ACCOUNT_NOT_REGISTED:
            send(session_socket,"account not registed",SOCKET_SIZE,0);
            return false;
        case SQL_WRONG_PASSWORD:
            send(session_socket,"wrong password",SOCKET_SIZE,0);
            return false;
        case SQL_FALSE:
            return false;
        case SQL_TRUE:
            send(session_socket,"log in succeed",SOCKET_SIZE,0);
            return true;
        default:
            cerr<<"chat_server:log in error"<<endl;
            exit(-1);
    }

}
void parseJson(const char *json_string,int session_socket){
    char out[16];
    if(get_Password("pass.dat",out)){
        cout<<"base64 decode succeed"<<endl;
    }
    DB db(out);

    json recv_json=json::parse(json_string);
    string flag=recv_json["flag"];
    switch(flag[0]){
        case SOCKET_LOG_UP:
            if(mid_Log_UP(db,json_string,session_socket)){
                cout<<"log up succeed!!!"<<endl;
            }else{
                cerr<<"log up failed!!!"<<endl;
            }
            break;
        case SOCKET_LOG_IN:
            if(mid_Log_IN(db,json_string,session_socket)){
                cout<<"log in succeed!!!"<<endl;
            }else{
                cerr<<"log in failed!!!"<<endl;
            }
            break;
        default:
            cerr<<"chat_server:parseJson error"<<endl;
            break;
    }
}

int main(){
    int server_socket=socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SERVER_PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(server_socket,(sockaddr *)&server_addr,sizeof(server_addr))<0){
        cerr<<"chat_server: main: server bind error"<<endl;
        exit(-1);
    }
    if(listen(server_socket,10)<0){
        cerr<<"chat_server: main: server listen error"<<endl;
        exit(-1);        
    }
    int epoll_fd=epoll_create(10);
    epoll_event socket_event,listen_event[MAX_LISTEN];
    socket_event.events=EPOLLIN; //TODO  LT/ET?  //高版本没有EPOLLLT,默认水平触发，一旦发现客户端的连接请求就持续建立连接
    socket_event.data.fd=server_socket;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,server_socket,&socket_event);
    while(1){
        cout<<"waiting for connection..."<<endl;
        int event_num=epoll_wait(epoll_fd,listen_event,MAX_LISTEN,-1); 
        if(event_num<-1){                               
            break;  //无连接则继续循环等待                                    
        }
        for(int i=0;i<event_num;i++){   //遍历返回事件,这里就是epoll和poll，select的区别，poll/select是遍历所有socket,而epoll返回的是有变化的socket
            if(!(listen_event[i].events & EPOLLIN)){
                continue;
            }
            if(listen_event[i].data.fd==server_socket){ //如果是server socket,说明有客户端发起连接请求，就建立新的连接
                sockaddr_in client_addr;
                socklen_t clinet_size=sizeof(sockaddr_in);
                int client_socket=accept(server_socket,(sockaddr *)&client_addr,&clinet_size);
                if(client_socket<0){    //连接建立失败,则跳过重连
                    continue;
                }else{
                    cout<<client_addr.sin_addr.s_addr<<":"<<client_addr.sin_port<<" connected"<<endl;
                }
                socket_event.events=EPOLLIN;
                socket_event.data.fd=client_socket;
                if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_socket,&socket_event)==-1){
                    cerr<<"client epoll_ctl error"<<endl;
                    exit(-1);
                } //将获取到的新连接加入到epoll实例中
            }else{//如果不是fd，说明是客户端发送了数据
                int session_socket=listen_event[i].data.fd; 	//获取连接，建立通信
                char *buff=(char*)malloc(SOCKET_SIZE);
                int ret = recv(session_socket,buff,SOCKET_SIZE,0); //非阻塞如果没有数据那么就返回-1
                if(ret==0){//读到0,说明客户端关闭,从epoll实例中删除客户端socket
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,session_socket,NULL);
                    close(session_socket);
                    cout<<session_socket<<" client closed connection"<<endl;
                }else if(ret<0){//出错,删除，报错
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,session_socket,NULL);
                    close(session_socket);
                    cerr<<session_socket<<" client recv error"<<endl;
                }else{//最后一种情况就只能是读到了数据
                    cout<<buff<<endl;//TODEL
                    try{
                        parseJson(buff,session_socket);
                    }
                    catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }
                    //finally
                    // close(session_socket);
                    
                    
                    
                    
                    // send(session_socket,"server recv message",50,0);
                }
                
                }
            }
        }
    close(epoll_fd);
    close(server_socket);
}

