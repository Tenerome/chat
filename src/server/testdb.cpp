#include<db.h>

int main(){
    DB db("123456");
    // if(DB_Log_UP(db,"test123","123456","TEST")){
    //     cout<<"log up succeed"<<endl;
    // }
    // if(DB_Log_IN(db,"test123","123456","127.0.0.1:2234")){
    //     cout<<"log in succeed"<<endl;
    // }
    if(DB_Log_OUT(db,"test123")){
        cout<<"log out succeed"<<endl;
    }

}