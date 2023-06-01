#include <tcpserver.h>
bool mid_Add_Contact(DB db,const char *json_string,int session_socket){//send add rquest
    json temp_json=json::parse(json_string);
    string account=temp_json["account"];
    string contact=temp_json["contact"];
    temp_json.clear();
    string contact_socket;
    switch(Send_Add_Contact_Request(db,account.c_str(),contact.c_str())){
        case SQL_ACCOUNT_NOT_REGISTED:
            temp_json["flag"]=SERVER_ACCOUNT_NOT_REGISTED;
            break;
        case SQL_ACCOUNT_ONLINE:
            temp_json["flag"]=SERVER_ADD_CONTACT_REQUEST;
            temp_json["contact"]=account;
            contact_socket=get_Route(db,contact.c_str());
            Send(route_socket[contact_socket],temp_json.dump().c_str());//to contact client
            return true;

        case SQL_BUFFER_ADD_CONTACT:
            temp_json["flag"]=SERVER_BUFFER_ADD_CONTACT;
            break;
        default:
            cerr<<"chat_server: mid add contact error"<<endl;
            // raise(SIGINT);
    }
    if(temp_json.empty()){
        return true;
    }else{
        Send(session_socket,temp_json.dump().c_str());
        return true;
    }
}

bool mid_Answer_Add_Contact(DB db,const char *json_string){
    json temp_json=json::parse(json_string);
    string answer_flag=temp_json["answer_flag"];
    string account=temp_json["account"];//accept
    string contact=temp_json["contact"];//request
    temp_json.clear();
    string contact_socket;
    if(stoi(answer_flag)==SERVER_AGREE_ADD_CONTACT){
        switch(Answer_Add_Contact(db,account.c_str(),contact.c_str(),1)){
            case SQL_ACCOUNT_ONLINE:
                if(!Add_Contact(db,account.c_str(),contact.c_str())){
                    cerr<<"add Contact error"<<endl;
                    // raise(SIGINT);
                }
                contact_socket=get_Route(db,contact.c_str());
                temp_json["flag"]=SERVER_ANSWER_YES;
                temp_json["contact"]=account;
                break;
            case SQL_BUFFER_ADD_CONTACT:
                break;
            default:
                cerr<<"mid Answer add Contact error"<<endl;
        }
    }else if(stoi(answer_flag)==SERVER_REJECT_ADD_CONTACT){
        switch(Answer_Add_Contact(db,account.c_str(),contact.c_str(),0)){
            case SQL_ACCOUNT_ONLINE:
                contact_socket=get_Route(db,contact.c_str());
                temp_json["flag"]=SERVER_ANSWER_NO;
                temp_json["contact"]=account;
                break;
            case SQL_BUFFER_ADD_CONTACT:
                break;
            default:
                cerr<<"mid Answer add Contact error"<<endl;
        }
    }else{
        cerr<<"chat_server:mid_answer_add_contact error"<<endl;
        // raise(SIGINT);
    }
    if(temp_json.empty()){
        return true;
    }else{
        Send(route_socket[contact_socket],temp_json.dump().c_str());
        return true;
    }
}

bool mid_Edit_Contact(DB db,const char *json_string,int session_socket){
    json temp_json=json::parse(json_string);
    string edit_flag=temp_json["edit_flag"];
    string account=temp_json["account"];
    string contact=temp_json["contact"];
    string nickname;
    bool ret=false;
    switch(stoi(edit_flag)){
        case SERVER_EDIT_NICKNAME:
            nickname=temp_json["nickname"];
            if(Set_Nickname(db,account.c_str(),contact.c_str(),nickname.c_str())){
                ret=true;
            }
            break;
        case SERVER_DELETE_CONTACT:
            if(Del_Contact(db,account.c_str(),contact.c_str())){
                ret=true;
            }
            break;
    }
    return ret;
}