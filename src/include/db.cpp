#include"db.h"

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
        cout<<"mysql close normally"<<endl;
    }
}
inline bool inline_get_Connection(DB *db){
    db->mysql=mysql_init(NULL);
    if(db->mysql==NULL){
        cerr<<"mysql_init error"<<endl;
        return false;
    }
    mysql_real_connect(db->mysql,db->host.c_str(),db->user.c_str(),db->password.c_str(),db->database.c_str(),db->port,NULL,0);
    if(db->mysql==NULL){
        cerr<<"mysql_real_connect error"<<endl;
        return false;
    }
    mysql_set_character_set(db->mysql,"utf8");
    return true;
}
bool DB_Log_UP(DB db, const char *account, const char *password, const char *name){
    if(!inline_get_Connection(&db)){
        cerr<<"inline_get_Connection error"<<endl;
        return false;
    }
    char query[250];
    sprintf(query,"insert into user(account,password,name) values('%s','%s','%s')",account,password,name);
    if(mysql_query(db.mysql,query)){
        cerr<<"insert error:"<<mysql_error(db.mysql)<<endl;
        return false;
    }else{
        return true;
    }
}
bool DB_Log_IN(DB db, const char *account, const char *password,const char *route){
    if(!inline_get_Connection(&db)){
        cerr<<"inline_get_Connection error"<<endl;
        return false;
    }
    //验证，getpass from mysql,strcmp(password,getpass)
    char query[250];
    sprintf(query,"select password from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"get password from mysql error:"<<mysql_error(db.mysql)<<endl;
       return false; 
    }
    MYSQL_RES* res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"mysql_store_result error:"<<mysql_error(db.mysql)<<endl;
        return false;
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    if(strcmp(row[0],MD5(password).toStr().c_str())!=0){
        cerr<<"密码输入错误，请重试"<<endl;
        return false;
    }
    mysql_free_result(res);
    //log in
    sprintf(query,"update user set status=1,route='%s' where account='%s'",route,account);
    if(mysql_query(db.mysql,query)){
        cerr<<"log in error:"<<mysql_error(db.mysql)<<endl;
        return false;
    }else{
        return true;
    }

}
