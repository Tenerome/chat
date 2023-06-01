#ifndef DB_H
    #define DB_H
#include"server.h"
class DB{
    public:
        MYSQL  *mysql;
        string password;
        string host;
        string user;
        string database;
        unsigned int port;
        DB(const  char *pass);
        DB(const char *pass,const char *host,const char *user,const char *database,unsigned int port);
};
class Message{
    public:
        string account;
        string contact;
        string message;
        string message_flag;
        Message(string account,string contact,string message,string message_flag){
            this->account=account;
            this->contact=contact;
            this->message=message;
            this->message_flag=message_flag;
        };
};
enum Exceptions{
    ERROR_SQL_PASSWORD=1,ERROR_SQL_CONNECTION,ERROR_SQL_QUERY,
    ERROR_SQL_RES_NULL
};
//global

bool get_Connection(DB &db);
bool check_Existed(DB &db,const char *account);
bool check_Online(DB &db,const char *account);
string getName_by_account(DB &db,const char *account);
string get_Route(DB &db,const char *account);
bool get_Profile(DB &db,const char *account,string &uid,string &name);
//user

int Log_UP(DB &db,const char *account,const char *password,const char *name);
int Log_IN(DB &db,const char *account,const char *password,const char *route);
int Log_OUT(DB &db,int session_socket);
//contacts

int Send_Add_Contact_Request(DB &db,const char *account,const char *contact);
int Add_Contact(DB &db,const char *account,const char *contact);
int Answer_Add_Contact(DB &db,const char *account,const char *contact,int answer);
bool get_Add_Flag(DB &db,const char *account,vector<string> &contact_add_list);
bool get_Answer_Add(DB &db,const char *account,vector<string> &agree_contact,vector<string> &reject_contact);
bool Get_Contact_List(DB &db,const char *account,map<string,string> &contact_list);
bool Set_Nickname(DB &db,const char *account,const char *contact,const char *nickname);
bool Del_Contact(DB &db,const char *account,const char *contact);

//message

int Send_Message(DB &db,const char *from_account,const char *to_account,const char *message,int message_type);
bool Get_Message_Buffer(DB &db,const char *account,vector<Message> &message_list);
bool Clear_Message_History(DB &db,const char *account);
bool Send_Group_Message(DB &db,const char *account,const char *message,int message_type,vector<string> &online_account_list);
bool Get_Group_Message(DB &db,vector<Message> &group_message_list);
#endif 