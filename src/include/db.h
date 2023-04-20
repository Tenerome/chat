#ifndef DB_H
    #define DB_H
//system
#include<mysql/mysql.h>
#include<cstring>
#include<stdio.h>
#include<iostream>
//include
#include<encode/md5.h>
#include<Signal&Macro.h>
using std::cout,std::endl,std::cerr;
using std::string;
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
        ~DB();
};
inline bool get_Connection(DB *db);
inline bool check_Existed(DB *db,const char *account);
inline bool check_Online(DB *db,const char *account);
int DB_Log_UP(DB db,const char *account,const char *password,const char *name);
int DB_Log_IN(DB db,const char *account,const char *password,const char *route);
int DB_Log_OUT(DB db,const char *account);
int DB_Add_Friend(DB db,const char *account,const char *friends);
int get_Route(DB db,const char *account,char *route);
#endif 