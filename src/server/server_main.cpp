#include <tcpserver.h>
map<string,int> route_socket;

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
    socket_event.events=EPOLLIN; //defalut:LT, use ET: EPOLLET|EPOLLIN
    socket_event.data.fd=server_socket;
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,server_socket,&socket_event);
    while(1){
        cout<<"waiting for connection..."<<endl;
        int event_num=epoll_wait(epoll_fd,listen_event,MAX_LISTEN,-1); //get the event number
        if(event_num<-1){                               
            break;  //if <0 then continue                                    
        }
        for(int i=0;i<event_num;i++){   //check all active event
            if(!(listen_event[i].events & EPOLLIN)){
                continue;
            }
            //if the event socket==server_socket, it is a new connection from one client
            if(listen_event[i].data.fd==server_socket){
                sockaddr_in client_addr;
                socklen_t clinet_size=sizeof(sockaddr_in);
                int client_socket=accept(server_socket,(sockaddr *)&client_addr,&clinet_size);
                if(client_socket<0){    //if connect failed,then pass this client,dicard the socket
                    continue;
                }else{
                    cout<<client_addr.sin_addr.s_addr<<":"<<client_addr.sin_port<<" connected"<<endl;
                }
                socket_event.events=EPOLLIN;
                socket_event.data.fd=client_socket;
                if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_socket,&socket_event)==-1){
                    cerr<<"client epoll_ctl error"<<endl;
                    exit(-1);
                } //add new the connected socket to epoll events
                //insert route_socket,use hash value obain the client_socket
                route_socket.insert(pair<string,int>(to_string(client_socket),client_socket));
            }else{//if the active event!=server_socket，it must be client send one message 
                int session_socket=listen_event[i].data.fd; 	//get client_socket
                string recv_string;
                int ret=Recv(session_socket,recv_string);
                if(ret==0){
                //if return 0,that is client close the connection ,delete client socket from epoll events,and delete the route_ip key-value
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,session_socket,NULL);
                    route_socket.erase(to_string(session_socket));//删除键值对
                    mid_Log_OUT(session_socket);//db log out
                    close(session_socket);
                    cout<<session_socket<<" client closed connection"<<endl;
                }else if(ret<0){//if ret<0,cerr
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,session_socket,NULL);
                    close(session_socket);
                    cerr<<session_socket<<" client recv error"<<endl;
                }else{//the last must be recv one message:
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

