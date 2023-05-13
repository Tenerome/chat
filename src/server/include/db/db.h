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
//global

bool get_Connection(DB &db);
bool check_Existed(DB &db,const char *account);
bool check_Online(DB &db,const char *account);
string getName_by_account(DB &db,const char *account);
string get_Route(DB &db,const char *account);
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
int Set_Nickname(DB &db,const char *account,const char *contact,const char *nickname);
int Del_Contact(DB &db,const char *account,const char *contact);

//message

int Send_Message(DB &db,const char *from_account,const char *to_account,const char *message,int message_type);
bool Get_Message_Buffer(DB &db,const char *account,map<string,string> &message_list);
bool Get_Image_Buffer(DB &db,const char *account,map<string,string> &image_list);
#endif 