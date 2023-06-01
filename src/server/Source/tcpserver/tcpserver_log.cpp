#include <tcpserver.h>
bool mid_Log_UP(DB db,const char *json_string,int session_socket){
    json temp_json=json::parse(json_string);
    string account=temp_json["account"];
    string name=temp_json["name"];
    string password=temp_json["password"];
    temp_json.clear();
    bool ret;
    switch(Log_UP(db,account.c_str(),password.c_str(),name.c_str())){
        case SQL_ACCOUNT_REGISTED:
            temp_json["flag"]=SERVER_ACCOUNT_REGISTED;
            ret=false;
            break;
        case SQL_FALSE:
            ret=false;
            break;
        case SQL_TRUE:
            temp_json["flag"]=SERVER_TRUE;
            ret=true;
            break;
        default:
            cerr<<"mid log up error"<<endl;
    }
    if(temp_json.empty()){
        return ret;
    }else{
        Send(session_socket,temp_json.dump().c_str());
        return ret;
    }

}
bool mid_Log_IN(DB db,const char *json_string,int session_socket){
    json temp_json=json::parse(json_string);
    string account=temp_json["account"];
    string password=temp_json["password"];
    temp_json.clear();
    bool ret;
    switch(Log_IN(db,account.c_str(),password.c_str(),to_string(session_socket).c_str())){
        case SQL_ACCOUNT_NOT_REGISTED:
            temp_json["flag"]=SERVER_ACCOUNT_NOT_REGISTED;
            ret=false;
            break;
        case SQL_WRONG_PASSWORD:
            temp_json["flag"]=SERVER_WRONG_PASSWORD;
            ret=false;
            break;
        case SQL_FALSE:
            ret=false;
            break;
        case SQL_TRUE:
            temp_json["flag"]=SERVER_TRUE;
            ret=true;
            break;
        default:
                cerr<<"mid log in error"<<endl;
    }
    if(temp_json.empty()){
        return ret;
    }else{
        Send(session_socket,temp_json.dump().c_str());
        return ret;
    }

}
void mid_Log_OUT(int session_socket){
    if(!check_Password(SQL_PASS_PATH)){
        cout<<"check mysql password wrong"<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_PASSWORD;
        return;
    }
    DB db(mysql_password.c_str());
    if(Log_OUT(db,session_socket)==SQL_TRUE){
        cout<<session_socket<<" log out succeed"<<endl;
    }
}