#ifndef STRUCT_H
    #define STRUCT_H
#include<Signal&Macro.h>
struct user_Property{
    //8位id;8位帐号，以字母开头;32位的密码md5值;name19位，中文最长6，英文最长18;ip+port 20位
    unsigned int status:1;
    unsigned int :4;//待利用
    unsigned int uid:27;
    char account[9];
    char password[33];
    char name[19];
    char route[21];
};
struct user_Message{
    char send_from_route[21];
    char send_to_route[21];
    char message_data[MESSAGE_SIZE];
    unsigned int message_type:8;
};

#define USER_PROPERTY_SIZE sizeof(user_Property)
#endif