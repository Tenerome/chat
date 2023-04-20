#include<db.h>

int main(){
    DB db("123456");
    if(DB_Log_IN(db,"test123","123456","127.0.0.1:2234")){
        cout<<"log in succeed"<<endl;
    }
    if(check_Online())
    // if(DB_Log_OUT(db,"test123")){
    //     cout<<"log out succeed"<<endl;
    // }

}