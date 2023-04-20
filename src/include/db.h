#ifndef DB_H
    #define DB_H
#include<mysql/mysql.h>
#include<cstring>
#include<iostream>
#include<encode/md5.h>
#include<stdio.h>
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
bool DB_Log_UP(DB db,const char *account,const char *password,const char *name);
bool DB_Log_IN(DB db,const char *account,const char *password,const char *route);
bool DB_Log_OUT(DB db,const char *account);
// char *get_Route(DB,db,const char *account);
#endif 