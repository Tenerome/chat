#ifndef SERVER_H
    #define SERVER_H
//cmake configure file
#define SERVER_PORT 8888
#define SQL_HOST "127.0.0.1"
#define SQL_USER "root"
#define SQL_DATABASE "chat"
#define SQL_PORT 3306
#define SQL_PASS_PATH "/home/tenerome/Documents/chat/src/server/build/pass.dat"
//system
#include<iostream>
#include<fstream>

#include<unistd.h>//IO and system
#include <csignal>

#include<string.h>//string

#include<mysql/mysql.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<sys/socket.h>//socket & mysql

#include<vector>
#include<map>//stl
//include
#include<Signal&Macro.h>
#include<base64.h>
#include<md5.h>
#include<json.hpp>

//namespace
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::string;
using std::stoi;//string to int
using std::to_string;//int to  string
using std::vector;
using std::map;
using std::multimap;
using std::pair;
using json=nlohmann::json;
#endif//SERVER_H
