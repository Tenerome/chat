#include<Struct.h>
#include<cstring>
#include<iostream>
#include<db.h>
#include<encode/md5.h>
using std::cout;

int main(){
    const char *str="123456";
    cout<<MD5(str).toStr().c_str()<<"  ";
}