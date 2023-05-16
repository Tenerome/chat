#include "chat_server.h"
map<string,int> route_socket;
void parseJson(const char *json_string,int session_socket){
    char out[16];
    if(!get_Password("pass.dat",out)){
        exit(-1);
    }
    DB db(out);
    
    json recv_json=json::parse(json_string);
    string flag=recv_json["flag"];
    switch(stoi(flag)){
        case SOCKET_LOG_UP:
            if(mid_Log_UP(db,json_string,session_socket)){
                cout<<session_socket<<" log up succeed"<<endl;
            }else{
                cerr<<session_socket<<" log up failed"<<endl;
            }
            break;
        case SOCKET_LOG_IN:
            if(mid_Log_IN(db,json_string,session_socket)){
                cout<<session_socket<<" log in succeed"<<endl;
            }else{
                cerr<<session_socket<<" log in failed"<<endl;
            }
            break;
        case SOCKET_ADD_CONTACT:
            if(mid_Add_Contact(db,json_string,session_socket)){
                cout<<session_socket<<" send add request succeed"<<endl;
            }else{
                cerr<<session_socket<<" send add request failed"<<endl;
            }
            break;
        case SOCKET_ANSWER_ADD:
            if(mid_Answer_Add_Contact(db,json_string)){
                cout<<session_socket<<" answer request succeed"<<endl;
            }else{
                cerr<<session_socket<<" answer request failed"<<endl;
            }
            break;
        case SOCKET_SELECT_WHEN_START:
            if(mid_Select_When_Start(db,json_string,session_socket)){
                cout<<session_socket<<" select buffer succeed"<<endl;
            }else{
                cerr<<session_socket<<" select buffer failed"<<endl;
            }
            break;
        case SOCKET_MESSAGE:
            if(mid_Send_Message(db,json_string,session_socket)){
                cout<<session_socket<<" send message succeed"<<endl;
            }else{
                cerr<<session_socket<<" send message failed"<<endl;
            }
            break;
        case SOCKET_EDIT_CONTACT:
            if(mid_Edit_Contact(db,json_string,session_socket)){
                cout<<session_socket<<" edit contact succeed"<<endl;
            }else{
                cerr<<session_socket<<" edit contact failed"<<endl;
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
                route_socket.insert(pair<string,int>(to_string(client_socket),client_socket));
            }else{//如果不是fd，说明是客户端发送了数据
                int session_socket=listen_event[i].data.fd; 	//获取连接，建立通信
                // char buff[SOCKET_SIZE];
                string recv_string;
                // int ret = recv(session_socket,buff,SOCKET_SIZE,0); //非阻塞如果没有数据那么就返回-1
                int ret=Recv(session_socket,recv_string);
                if(ret==0){//读到0,说明客户端关闭,从epoll实例中删除客户端socket,并删除ip_socket键值对
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,session_socket,NULL);
                    route_socket.erase(to_string(session_socket));//删除键值对
                    mid_Log_OUT(session_socket);//db log out
                    close(session_socket);
                    cout<<session_socket<<" client closed connection"<<endl;
                }else if(ret<0){//出错,删除，报错
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,session_socket,NULL);
                    close(session_socket);
                    cerr<<session_socket<<" client recv error"<<endl;
                }else{//最后一种情况就只能是读到了数据
                    cout<<"<Recv>:"<<recv_string<<endl;//TODEL
                    try{
                        parseJson(recv_string.c_str(),session_socket);
                    }
                    catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }
                    //clear buff

                }
                
                }
            }
        }
    close(epoll_fd);
    close(server_socket);
}

