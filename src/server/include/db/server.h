#ifndef SERVER_H
    #define SERVER_H
//system
#include<iostream>
#include<fstream>
// #include<stdio.h>
#include<unistd.h>//IO and system

// #include<cstring>
#include<string.h>//string

#include<mysql/mysql.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<sys/socket.h>//socket & mysql

#include<vector>
#include<map>//stl
//include
#include<Signal&Macro.h>
#include<encode/base64.h>
#include<json.hpp>
#include<encode/md5.h>

//namespace
using std::cout,std::endl,std::cerr;
using std::ifstream;
using std::string;
using std::stoi;//string to int
using std::to_string;//int to  string
using std::vector;
using std::map;
using std::pair;
using json=nlohmann::json;
#endif//SERVER_H