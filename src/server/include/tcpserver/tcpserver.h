#ifndef CHAT_SERVER_H
    #define CHAT_SERVER_H

#include <db.h>
//global variable

extern map<string,int> route_socket;//declare but not define
extern string mysql_password;
//functions
//global

void Send(int socket,const char *buffer);
int Recv(int socket,string &recv_string);
bool check_Password(const char *path);
//log

bool mid_Log_UP(DB db,const char *json_string,int session_socket);
bool mid_Log_IN(DB db,const char *json_string,int session_socket);
void mid_Log_OUT(int session_socket);
//contact

bool mid_Add_Contact(DB db,const char *json_string,int session_socket);
bool mid_Answer_Add_Contact(DB db,const char *json_string);
bool mid_Edit_Contact(DB db,const char *json_string,int session_socket);
//message

bool mid_Select_When_Start(DB db,const char *json_string,int session_socket);
bool mid_Send_Message(DB db,const char *json_string,int session_socket);
bool mid_Clear_Message_History(DB db,const char *json_string,int session_socket);
//main

void parseJson(const char *json_string,int session_socket);

#endif