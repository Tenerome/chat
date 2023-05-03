#ifndef SIGNAL_MACRO_H
    #define SIGNAL__MACRO_H
//=====signal======
//sql signal
#define SQL_FALSE 0
#define SQL_TRUE 1
#define SQL_ACCOUNT_REGISTED 3
#define SQL_ACCOUNT_NOT_REGISTED 4
#define SQL_WRONG_PASSWORD 5
#define SQL_ACCOUNT_ONLINE 6
#define SQL_BUFFER_ADD_CONTACT 7
#define SQL_BUFFER_SEND_MESSAGE 8
//===========socket signal======
#define SOCKET_LOG_UP 0
#define SOCKET_LOG_IN 1
//message flag
#define TEXT_MESSAGE 0
#define IMAGE_MESSAGE 1
#define VOICE_MESSAGE 3
//======macro======
#define MESSAGE_SIZE 1024
#define MAX_LISTEN 1024
#endif