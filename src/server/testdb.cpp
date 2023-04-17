#include<Struct.h>
#include<cstring>
#include<iostream>
#include<db.h>
#include<encode/md5.h>
using std::cout;

int main(){
    DB db("123456");
    DB_Log_UP(db,"test","test123","TEST");
}