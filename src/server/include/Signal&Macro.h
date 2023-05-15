#ifndef SIGNAL_MACRO_H
    #define SIGNAL__MACRO_H
//=====signal======
//SQL0-9
#define SQL_FALSE 0
#define SQL_TRUE 1
#define SQL_ACCOUNT_REGISTED 2
#define SQL_ACCOUNT_NOT_REGISTED 3
#define SQL_WRONG_PASSWORD 4
#define SQL_ACCOUNT_ONLINE 5
#define SQL_BUFFER_ADD_CONTACT 6
#define SQL_BUFFER_SEND_MESSAGE 7
#define SQL_AGREE_ADD 8
#define SQL_REJECT_ADD 9
//===========socket signal======
//10-29
#define SOCKET_LOG_UP 10
#define SOCKET_LOG_IN 11
#define SOCKET_ADD_CONTACT 12
#define SOCKET_ANSWER_ADD 13
#define SOCKET_SELECT_WHEN_START 14
#define SOCKET_MESSAGE 15
#define SOCKET_EDIT_CONTACT 16
#define SOCKET_GET_RPOFILE 17
//SERVER signal
//30->
#define SERVER_FALSE 30
#define SERVER_TRUE 31
#define SERVER_ACCOUNT_REGISTED 32
#define SERVER_ACCOUNT_NOT_REGISTED 33
#define SERVER_WRONG_PASSWORD 34
#define SERVER_ACCOUNT_ONLINE 35
#define SERVER_BUFFER_ADD_CONTACT 36
#define SERVER_BUFFER_SEND_MESSAGE 37
#define SERVER_ADD_CONTACT_REQUEST 38
#define SERVER_AGREE_ADD_CONTACT  39
#define SERVER_REJECT_ADD_CONTACT  40
#define SERVER_ANSWER_YES 41
#define SERVER_ANSWER_NO 42
#define SERVER_CONTACT_LIST 43
#define SERVER_TEXT_MESSAGE 44
#define SERVER_EDIT_NICKNAME  45
#define SERVER_DELETE_CONTACT  46
#define SERVER_GROUP_MESSAGE 47
//======macro======
#define SOCKET_SIZE 2048
#define MAX_LISTEN 1024
#endif