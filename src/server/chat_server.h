#ifndef CHAT_SERVER_H
    #define CHAT_SERVER_H

#define SERVER_PORT 8888
//server
#include "db.h"
//lib
#include<Signal&Macro.h>
#include<base64.h>
#include<json.hpp>
//system
#include<iostream>
#include<fstream>
#include<string.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

using std::cout,std::endl,std::cerr,std::cin;
using std::ifstream;
using std::string;
using json=nlohmann::json;
#endif