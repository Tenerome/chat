#include"db.h"
//==================构造和析构=======================

DB::DB(const char *pass):DB(pass,"127.0.0.1","root","chat",3306){}
DB::DB(const char *pass,const char *host,const char *user,const char *database,unsigned int port){
    this->password=pass;
    this->host=host;
    this->user=user;
    this->database=database;
    this->port=port;
}
DB::~DB(){
    if(mysql!=NULL){
        mysql_close(mysql);
    }
}

//=======================inline，复用的函数=============

//connect to mysql
inline bool get_Connection(DB *db){
    db->mysql=mysql_init(NULL);
    if(db->mysql==NULL){
        cerr<<"db-get_Connection:mysql_init error"<<endl;
        return false;
    }
    mysql_real_connect(db->mysql,db->host.c_str(),db->user.c_str(),db->password.c_str(),db->database.c_str(),db->port,NULL,0);
    if(db->mysql==NULL){
        cerr<<"db-get_Connection:mysql_real_connect error"<<endl;
        return false;
    }
    mysql_set_character_set(db->mysql,"utf8");
    return true;
}
//check account has been/not been registed
inline bool check_Existed(DB *db,const char *account){
    char query[250];
    sprintf(query,"select count(1) from user where account='%s' ",account);
    if(mysql_query(db->mysql,query)){
        cerr<<"db-Check_Existed:select error:"<<mysql_error(db->mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db->mysql);
    if(res==NULL){
        cerr<<"db-inline_Check_Existed:res error:"<<mysql_error(db->mysql)<<endl;
        exit(-1);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    if(strcmp(row[0],"1")==0){
        return true;
    }else{
        return false;
    }
}
//check account online status
inline bool check_Online(DB *db,const char *account){
    char query[250];
    sprintf(query,"select status from user where account='%s'",account);
    if(mysql_query(db->mysql,query)){
        cerr<<"db-check_Online:get status error:"<<mysql_error(db->mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db->mysql);
    if(res==NULL){
        cerr<<"db-Check_Online:res error:"<<mysql_error(db->mysql)<<endl;
        exit(-1);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    if(strcmp(row[0],"1")==0){
        return true;
    }else{
        return false;
    }

}

//=================状态更新===========================

//account log up,return values:
//SIGNAL_ACCOUNT_REGISTED
//SIGNAL_FALSE / SIGNAL_TRUE
int DB_Log_UP(DB db, const char *account, const char *password, const char *name){
    if(!get_Connection(&db)){
        exit(-1);
    }
    if(check_Existed(&db,account)){
        cout<<account<<" has been registed"<<endl;
        return SIGNAL_ACCOUNT_REGISTED;
    }
    char query[250];
    sprintf(query,"insert into user(account,password,name) values('%s','%s','%s')",account,password,name);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-DB_Log_UP:insert error:"<<mysql_error(db.mysql)<<endl;
        return SIGNAL_FALSE;
    }else{
        return SIGNAL_TRUE;
    }
}
//account log in,return values:
//SIGNAL_ACCOUNT_NOT_REGISTED
//SIGNAL_WRONG_PASSWORD
//SIGNAL_FALSE / SIGNAL_TRUE
int DB_Log_IN(DB db, const char *account, const char *password,const char *route){

    if(!get_Connection(&db)){
        exit(-1);
    }
    if(!check_Existed(&db,account)){
        cout<<account<<"does not exist"<<endl;
        return SIGNAL_ACCOUNT_NOT_REGISTED;
    }
    //验证，getpass from mysql,strcmp(password,getpass)
    char query[250];
    sprintf(query,"select password from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-DB_Log_IN:get password error:"<<mysql_error(db.mysql)<<endl;
       exit(-1);
    }
    MYSQL_RES* res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-DB_Log_IN:mysql_store_result error:"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    // if(strcmp(row[0],MD5(password).toStr().c_str())!=0){
    if(strcmp(row[0],password)!=0){
        cout<<"password error,please input again"<<endl;
        return SIGNAL_WRONG_PASSWORD;
    }
    mysql_free_result(res);
    //log in
    sprintf(query,"update user set status=1,route='%s' where account='%s'",route,account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-DB_Log_IN:log in error:"<<mysql_error(db.mysql)<<endl;
        return SIGNAL_FALSE;
    }else{
        return SIGNAL_TRUE;
    }
}
//account actively log out,return vales:
//SIGNAL_FALSE / SIGNAL_TRUE
int DB_Log_OUT(DB db,const char *account){
    if(!get_Connection(&db)){
        exit(-1);
    }
    char query[250];
    sprintf(query,"update user set status=0,route='NULL' where account ='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-DB_Log_OUT:log out error:"<<mysql_error(db.mysql)<<endl;
       return SIGNAL_FALSE; 
    }
    return SIGNAL_TRUE;
}
//==========================好友================

int DB_Add_Friend(DB db,const char *account,const char *friends){
    if(!get_Connection(&db)){
        exit(-1);
    }
    if(!check_Existed(&db,account)){
        cout<<account<<"does not exist"<<endl;
        return SIGNAL_ACCOUNT_NOT_REGISTED;
    }
    if(check_Online(&db,account)){
        //发送申请请求
        
    }else{
        //添加到缓存表
    }
}

// bool get_Route(DB db,const char *account,char *route){
//     if(!get_Connection(&db)){
//         exit(-1);
//     }
//     char query[250];
//     sprintf(query,"select route from user where account='%s'",account);
//     if(mysql_query(db.mysql,query)){
//        cerr<<"db-get_Route:get route error:"<<mysql_error(db.mysql)<<endl;
//        return false; 
//     }
//     MYSQL_RES *res=mysql_store_result(db.mysql);
//     if(res==NULL){
//         cerr<<"db-get_Route:mysql store result error:"<<mysql_error(db.mysql);
//         return false;
//     }
//     MYSQL_ROW row=mysql_fetch_row(res);
//     mysql_free_result(res);
//     strcpy(route,row[0]);
// }
