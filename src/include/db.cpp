#include"db.h"

DB::DB(const char *pass){
    new (this)DB(pass,"127.0.0.1","root","chat",3306);
}
DB::DB(const char *pass,const char *host,const char *user,const char *database,unsigned int port){
    this->password=pass;
    this->host=host;
    this->user=user;
    this->database=database;
    this->port=port;
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
    return true;
}
bool DB_Log_UP(DB db, const char *account, const char *password, const char *name){
    if(!inline_get_Connection(&db)){
        cerr<<"inline_get_Connection error"<<endl;
        return false;
    }
    char query[250];
    sprintf(query,"insert into user(account,password,name) values(\'%s\',\'%s\',\'%s\')",account,password,name);
    if(mysql_query(db.mysql,query)){
        cerr<<"insert error:"<<mysql_error(db.mysql)<<endl;
        return false;
    }else{
        mysql_close(db.mysql);
        return true;
    }
}

bool DB_Log_IN(DB db, const char *account, const char *password,const char *route)
{
    db.mysql=mysql_init(NULL);
    if(db.mysql==NULL){
        cerr<<"mysql_init error"<<endl;
        return false;
    }
    db.mysql=mysql_real_connect(db.mysql,db.host.c_str(),db.user.c_str(),db.password.c_str(),db.database.c_str(),db.port,NULL,0);
    if(db.mysql==NULL){
        cerr<<"mysql_real_connect error"<<endl;
        return false;
    }
    char query[250];
    // sprintf(query,"");
    return true;
}
