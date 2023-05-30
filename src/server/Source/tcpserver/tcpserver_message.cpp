#include <tcpserver.h>

bool mid_Select_When_Start(DB db,const char *json_string,int session_socket){
    json temp_json=json::parse(json_string);
    string account=temp_json["account"];
    temp_json.clear();
    //get profile
    string uid;
    string name;
    if(get_Profile(db,account.c_str(),uid,name)){
            temp_json["flag"]=SOCKET_GET_RPOFILE;
            temp_json["uid"]=uid;
            temp_json["name"]=name;
            Send(session_socket,temp_json.dump().c_str());
    }
    temp_json.clear();
    //get add request
    vector<string> contact_add_list;
    if(get_Add_Flag(db,account.c_str(),contact_add_list)){
        for(auto it=contact_add_list.begin();it!=contact_add_list.end();++it){
            temp_json["flag"]=SERVER_ADD_CONTACT_REQUEST;
            temp_json["contact"]=*it;
            Send(session_socket,temp_json.dump().c_str());
        }
    }
    temp_json.clear();
    //get answer add
    auto &agree_contact=contact_add_list;//recycle
    agree_contact.clear();
    vector<string> reject_contact;
    if(get_Answer_Add(db,account.c_str(),agree_contact,reject_contact)){
        if(!agree_contact.empty()){
            for(auto it=agree_contact.begin();it!=agree_contact.end();++it){
                temp_json["flag"]=SERVER_ANSWER_YES;
                temp_json["contact"]=*it;
                Send(session_socket,temp_json.dump().c_str());
            }
        }
        temp_json.clear();
        if(!reject_contact.empty()){
            for(auto it=reject_contact.begin();it!=reject_contact.end();++it){
                temp_json["flag"]=SERVER_ANSWER_NO;
                temp_json["contact"]=*it;
                Send(session_socket,temp_json.dump().c_str());
            }
        }
    }
    temp_json.clear();
    //getlist
    map<string,string> contact_list;
    if(Get_Contact_List(db,account.c_str(),contact_list)){
        temp_json["flag"]=SERVER_CONTACT_LIST;
        for(auto it=contact_list.begin();it!=contact_list.end();++it){
            temp_json[it->first]=it->second;
        }
        Send(session_socket,temp_json.dump().c_str());
    }
    temp_json.clear();

    //get message buffer
    vector<Message> message_list;
    if(Get_Message_Buffer(db,account.c_str(),message_list)){
        temp_json["flag"]=SERVER_TEXT_MESSAGE;
        for(auto it=message_list.begin();it!=message_list.end();++it){
            temp_json["contact"]=it->contact;
            temp_json["message"]=it->message;
            temp_json["message_flag"]=strcmp(it->message_flag.c_str(),"0")==0?SERVER_TEXT_MESSAGE:SERVER_IMAGE_MESSAGE;
            Send(session_socket,temp_json.dump().c_str());
        }
        
    }
    temp_json.clear();
    //get chatroom history
    vector<pair<string,string>> group_list;
    if(Get_Group_Message(db,group_list)){
        temp_json["flag"]=SERVER_GROUP_MESSAGE;
        for(auto it=group_list.begin();it!=group_list.end();++it){
            temp_json["contact"]=it->first;
            temp_json["message"]=it->second;
            Send(session_socket,temp_json.dump().c_str());
        }
    }
    temp_json.clear();
    return true;
}



bool mid_Send_Message(DB db,const char *json_string,int session_socket){
    json temp_json=json::parse(json_string);
    string message_flag=temp_json["message_flag"];
    string account=temp_json["account"];
    string contact=temp_json["contact"];
    string message=temp_json["message"];
    temp_json.clear();
    string contact_socket;
    if(strcmp(contact.c_str(),"$chatroom")==0){
        vector<string> online_account_list;
        if(Send_Group_Message(db,account.c_str(),message.c_str(),online_account_list)){
            for(auto it=online_account_list.begin();it!=online_account_list.end();it++){
                contact_socket=get_Route(db,(*it).c_str());
                temp_json["flag"]=SERVER_GROUP_MESSAGE;
                temp_json["contact"]=account;
                temp_json["message"]=message;
                Send(route_socket[contact_socket],temp_json.dump().c_str());
            }
        }
        return true;
    }else{
        switch (stoi(message_flag)){
            case SERVER_TEXT_MESSAGE:
                switch (Send_Message(db,account.c_str(),contact.c_str(),message.c_str(),0)){
                    case SQL_ACCOUNT_ONLINE:
                        contact_socket=get_Route(db,contact.c_str());
                        temp_json["flag"]=SERVER_TEXT_MESSAGE;
                        temp_json["message"]=message;
                        temp_json["contact"]=account;
                        temp_json["message_flag"]=message_flag;
                        Send(route_socket[contact_socket],temp_json.dump().c_str());
                        return true;
                    case SQL_BUFFER_SEND_MESSAGE:
                        return false;
                }
            break;
        
            case SERVER_IMAGE_MESSAGE:
                switch (Send_Message(db,account.c_str(),contact.c_str(),message.c_str(),1)){
                    case SQL_ACCOUNT_ONLINE:
                        contact_socket=get_Route(db,contact.c_str());
                        temp_json["flag"]=SERVER_TEXT_MESSAGE;
                        temp_json["message"]=message;
                        temp_json["contact"]=account;
                        temp_json["message_flag"]=message_flag;
                        Send(route_socket[contact_socket],temp_json.dump().c_str());
                        return true;
                    case SQL_BUFFER_SEND_MESSAGE:
                        return false;
                }
            break;
        }
        return true;
    }
}