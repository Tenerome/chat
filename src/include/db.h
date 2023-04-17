#ifndef DB_H
    #define DB_H
#include<mysql/mysql.h>
#include<string>
#include<iostream>
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
};
inline bool inline_get_Connection(DB *db);
bool DB_Log_UP(DB db,const char *account,const char *password,const char *name);
bool DB_Log_IN(DB db,const char *account,const char *password,const char *route);
#endif 