#ifndef DB_H
    #define DB_H
//system
#include<mysql/mysql.h>
#include<cstring>
#include<stdio.h>
#include<iostream>
#include<vector>
//include
#include<encode/md5.h>
#include<Signal&Macro.h>
using std::cout,std::endl,std::cerr;
using std::string;
using std::vector;
using std::stoi;//string to int
using std::to_string;
class DB{
    public:
        MYSQL *mysql;
        string password;
        string host;
        string user;
        string database;
        unsigned int port;
        DB(const  char *pass);
        DB(const char *pass,const char *host,const char *user,const char *database,unsigned int port);
};
//inline

inline bool get_Connection(DB *db);
inline bool check_Existed(DB *db,const char *account);
inline bool check_Online(DB *db,const char *account);
inline string getName_by_account(DB *db,const char *account);

//get
string get_Route(DB db,const char *account);
bool get_Add_Flag(DB db,const char *account,vector<string> &contact_add_list);
bool get_Answer_Add(DB db,const char *account,vector<string> &agree_contact,vector<string> &reject_contact);
//user

int Log_UP(DB db,const char *account,const char *password,const char *name);
int Log_IN(DB db,const char *account,const char *password,const char *route);
int Log_OUT(DB db,int session_socket);
//contacts

int Send_Add_Contact_Request(DB db,const char *account,const char *contact);
int Add_Contact(DB db,const char *account,const char *contact);
int Answer_Add_Contact(DB db,const char *account,const char *contact,int answer);
int Set_Nickname(DB db,const char *account,const char *contact,const char *nickname);
int Del_Contact(DB db,const char *account,const char *contact);
vector<string> Get_Contact_List(DB db,const char *account);
//message

int Before_Send_Message(DB db,const char *from_account,const char *to_account,const char *message);
int Get_New_Contact(DB db,const char *account);
string Get_Message_Buffer(DB db,const char *account);
#endif 