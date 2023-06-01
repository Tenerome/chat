#include <tcpserver.h>
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
bool check_Password(const char *path){
    char in[250];
    char out[250];
    ifstream(path)>>in;
    if(base64_decode(in,strlen(in),(unsigned char*)out)==0){
        cerr<<"base64 decode failed,maybe you need to run as root or check other configure"<<endl;
        return false;
    }
    out[strlen((char*)out)]='\0';//add end tag 
    if(strcmp(MD5(mysql_password).toStr().c_str(),out)==0){
        return true;
    }else{
        return false;
    }
}
void parseJson(const char *json_string,int session_socket){
    if(!check_Password(SQL_PASS_PATH)){
        cerr<<"mysql password wrong"<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_PASSWORD;
        return;
    }
    DB db(mysql_password.c_str());
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
        case SOCKET_CLEAR_MESSAGE_HISTORY:
            if(mid_Clear_Message_History(db,json_string,session_socket)){
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