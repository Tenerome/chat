#include <db.h>
//account log up,return values:
//SQL_ACCOUNT_REGISTED
//SQL_FALSE / SQL_TRUE
int Log_UP(DB &db, const char *account, const char *password, const char *name){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    if(check_Existed(db,account)){
        cout<<account<<" has been registed"<<endl;
        mysql_close(db.mysql);
        return SQL_ACCOUNT_REGISTED;
    }
    char query[250];
    sprintf(query,"insert into user(account,password,name,status,route) values('%s','%s','%s','%d','%d')",account,password,name,0,-1);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Log_UP:insert error:"<<mysql_error(db.mysql)<<endl;
        mysql_close(db.mysql);
        return SQL_FALSE;
    }else{
        mysql_close(db.mysql);
        return SQL_TRUE;
    }
}
//account log in,return values:
//SQL_ACCOUNT_NOT_REGISTED
//SQL_WRONG_PASSWORD
//SQL_FALSE / SQL_TRUE
int Log_IN(DB &db, const char *account, const char *password,const char *route){

    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    if(!check_Existed(db,account)){
        cout<<account<<"does not exist"<<endl;
        mysql_close(db.mysql);
        return SQL_ACCOUNT_NOT_REGISTED;
    }
    //验证，getpass from mysql,strcmp(password,getpass)
    char query[250];
    sprintf(query,"select password from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-Log_IN:get password error:"<<mysql_error(db.mysql)<<endl;
    //    raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES* res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Log_IN:mysql_store_result error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    // if(strcmp(row[0],MD5(password).toStr().c_str())!=0){
    if(strcmp(row[0],password)!=0){
        cout<<"password error,please input again"<<endl;
        mysql_close(db.mysql);
        return SQL_WRONG_PASSWORD;
    }
    //log in
    sprintf(query,"update user set status=1,route='%s' where account='%s'",route,account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Log_IN:log in error:"<<mysql_error(db.mysql)<<endl;
        mysql_close(db.mysql);
        return SQL_FALSE;
    }else{
        mysql_close(db.mysql);
        return SQL_TRUE;
    }
}
//account actively log out,return vales:
//SQL_FALSE / SQL_TRUE
int Log_OUT(DB &db,int session_socket){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    char query[250];
    sprintf(query,"update user set status=0,route=-1 where route ='%d'",session_socket);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-Log_OUT:log out error:"<<mysql_error(db.mysql)<<endl;
       mysql_close(db.mysql);
       return SQL_FALSE; 
    }
    mysql_close(db.mysql);
    return SQL_TRUE;
}