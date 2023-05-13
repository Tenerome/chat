#ifndef SIGNAL_MACRO_H
    #define SIGNAL__MACRO_H
//=====signal======
//SQL
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
//SERVER signal
#define SERVER_FALSE 0
#define SERVER_TRUE 1
#define SERVER_ACCOUNT_REGISTED 2
#define SERVER_ACCOUNT_NOT_REGISTED 3
#define SERVER_WRONG_PASSWORD 4
#define SERVER_ACCOUNT_ONLINE 5
#define SERVER_BUFFER_ADD_CONTACT 6
#define SERVER_BUFFER_SEND_MESSAGE 7
#define SERVER_ADD_CONTACT_REQUEST 8
#define SERVER_AGREE_ADD_CONTACT  9
#define SERVER_REJECT_ADD_CONTACT  10
#define SERVER_ANSWER_YES 11
#define SERVER_ANSWER_NO 12
#define SERVER_CONTACT_LIST 13
#define SERVER_TEXT_MESSAGE 14
//===========socket signal======
#define SOCKET_LOG_UP 0
#define SOCKET_LOG_IN 1
#define SOCKET_ADD_CONTACT 2
#define SOCKET_ANSWER_ADD 3
#define SOCKET_SELECT_WHEN_START 4
#define SOCKET_MESSAGE 5
//message flag
#define TEXT_MESSAGE 0
#define IMAGE_MESSAGE 1
#define VOICE_MESSAGE 3
//======macro======
#define SOCKET_SIZE 2048
#define MAX_LISTEN 1024
#endif