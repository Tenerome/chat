#include <db.h>
//==================DB constructors=======================

DB::DB(const char *pass):DB(pass,SQL_HOST,SQL_USER,SQL_DATABASE,SQL_PORT){}
DB::DB(const char *pass,const char *host,const char *user,const char *database,unsigned int port){
    this->password=pass;
    this->host=host;
    this->user=user;
    this->database=database;
    this->port=port;
}


//connect to mysql
bool get_Connection(DB &db){
    db.mysql=mysql_init(NULL);
    // mysql_init(db.mysql);
    if(db.mysql==NULL){
        cerr<<"db-get_Connection:mysql_init error"<<endl;
        return false;
    }
    mysql_real_connect(db.mysql,db.host.c_str(),db.user.c_str(),db.password.c_str(),db.database.c_str(),db.port,NULL,0);
    if(db.mysql==NULL){
        cerr<<"db-get_Connection:mysql_real_connect error"<<endl;
        return false;
    }
    mysql_set_character_set(db.mysql,"utf8");
    return true;
}
//check account has been/not been registed
//!need getConnectin before check
bool check_Existed(DB &db,const char *account){
    char query[250];
    sprintf(query,"select count(1) from user where account='%s' ",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Check_Existed:select error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-inline_Check_Existed:res error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    //typeid(row[0])name==Pc，it's a char pointer type: char*
    if(strcmp(row[0],"1")==0){
        return true;
    }else{
        return false;
    }
}
//check account online status
//!need getConnectin before check
bool check_Online(DB &db,const char *account){
    char query[250];
    sprintf(query,"select status from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-check_Online:get status error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Check_Online:res error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    if(strcmp(row[0],"1")==0){
        return true;
    }else{
        return false;
    }

}
//!need getConnectin before get
string getName_by_account(DB &db,const char *account){
    char query[250];
    sprintf(query,"select name from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-getName_by_account:select error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return "";
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-get_Name_by_account:mysql store result error:"<<mysql_error(db.mysql);
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return "";
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    return row[0];
}

//return account socket
//complete function with getConnection and close mysql
//don't use if there is another sql event below
string get_Route(DB &db,const char *account){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return "";
    }
    char query[250];
    sprintf(query,"select route from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-get_Route:get route error:"<<mysql_error(db.mysql)<<endl;
    //    raise(SIGINT); 
        throw ERROR_SQL_QUERY;
        return "";
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-get_Route:mysql store result error:"<<mysql_error(db.mysql);
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return "";
    }
    if(mysql_num_rows(res)==0){
        cerr<<"no log in information"<<endl;
        // raise(SIGINT);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    mysql_close(db.mysql);
    return row[0];
}

//transmit uid and name
//complete function with getConnection and close mysql
//don't use if there is another sql event below
bool get_Profile(DB &db,const char *account,string &uid,string &name){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    char query[250];
    sprintf(query,"select uid,name from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-get_Route:get route error:"<<mysql_error(db.mysql)<<endl;
    //    raise(SIGINT); 
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-get_Route:mysql store result error:"<<mysql_error(db.mysql);
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    if(mysql_num_rows(res)==0){
        cerr<<"no log in information"<<endl;
        // raise(SIGINT);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    uid=row[0];
    name=row[1];
    mysql_free_result(res);
    mysql_close(db.mysql);
    return true;
}
