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

inline string getName_by_account(DB *db,const char *account){
    char query[250];
    sprintf(query,"select name from user where account='%s'",account);
    if(mysql_query(db->mysql,query)){
        cerr<<"db-getName_by_account:select error:"<<mysql_error(db->mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db->mysql);
    if(res==NULL){
        cerr<<"db-get_Name_by_account:mysql store result error:"<<mysql_error(db->mysql);
        exit(-1);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    return row[0];
}
inline string get_Route(DB *db,const char *account){
    char query[250];
    sprintf(query,"select route from user where account='%s'",account);
    if(mysql_query(db->mysql,query)){
       cerr<<"db-get_Route:get route error:"<<mysql_error(db->mysql)<<endl;
       exit(-1); 
    }
    MYSQL_RES *res=mysql_store_result(db->mysql);
    if(res==NULL){
        cerr<<"db-get_Route:mysql store result error:"<<mysql_error(db->mysql);
        exit(-1);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    return row[0];
}
inline bool Check_Add_Flag(DB *db,const char *account){
    char query[250];
    sprintf(query,"select add_flag from message where account='%s'",account);
    if(mysql_query(db->mysql,query)){
        cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db->mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db->mysql);
    if(res==NULL){
        cerr<<"db-Get_Add_Buffer:store result error"<<mysql_error(db->mysql)<<endl;
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
//SQL_ACCOUNT_REGISTED
//SQL_FALSE / SQL_TRUE
int Log_UP(DB db, const char *account, const char *password, const char *name){
    if(!get_Connection(&db)){
        exit(-1);
    }
    if(check_Existed(&db,account)){
        cout<<account<<" has been registed"<<endl;
        return SQL_ACCOUNT_REGISTED;
    }
    char query[250];
    sprintf(query,"insert into user(account,password,name) values('%s','%s','%s')",account,password,name);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Log_UP:insert error:"<<mysql_error(db.mysql)<<endl;
        return SQL_FALSE;
    }else{
        return SQL_TRUE;
    }
}
//account log in,return values:
//SQL_ACCOUNT_NOT_REGISTED
//SQL_WRONG_PASSWORD
//SQL_FALSE / SQL_TRUE
int Log_IN(DB db, const char *account, const char *password,const char *route){

    if(!get_Connection(&db)){
        exit(-1);
    }
    if(!check_Existed(&db,account)){
        cout<<account<<"does not exist"<<endl;
        return SQL_ACCOUNT_NOT_REGISTED;
    }
    //验证，getpass from mysql,strcmp(password,getpass)
    char query[250];
    sprintf(query,"select password from user where account='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-Log_IN:get password error:"<<mysql_error(db.mysql)<<endl;
       exit(-1);
    }
    MYSQL_RES* res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Log_IN:mysql_store_result error:"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    MYSQL_ROW row=mysql_fetch_row(res);
    mysql_free_result(res);
    // if(strcmp(row[0],MD5(password).toStr().c_str())!=0){
    if(strcmp(row[0],password)!=0){
        cout<<"password error,please input again"<<endl;
        return SQL_WRONG_PASSWORD;
    }
    //log in
    sprintf(query,"update user set status=1,route='%s' where account='%s'",route,account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Log_IN:log in error:"<<mysql_error(db.mysql)<<endl;
        return SQL_FALSE;
    }else{
        return SQL_TRUE;
    }
}
//account actively log out,return vales:
//SQL_FALSE / SQL_TRUE
int Log_OUT(DB db,const char *account){
    if(!get_Connection(&db)){
        exit(-1);
    }
    char query[250];
    sprintf(query,"update user set status=0,route='NULL' where account ='%s'",account);
    if(mysql_query(db.mysql,query)){
       cerr<<"db-Log_OUT:log out error:"<<mysql_error(db.mysql)<<endl;
       return SQL_FALSE; 
    }
    return SQL_TRUE;
}
//==========================好友================

//before add contact works:return values:
//SQL_ACCOUNT_NOT_REGISTED
//SQL_ACCOUNT_ONLINE
//SQL_BUFFER_ADD_CONTACT
int Before_Add_Contact(DB db,const char *account,const char *contact){
    if(!get_Connection(&db)){
        exit(-1);
    }
    if(!check_Existed(&db,contact)){
        cout<<contact<<"does not exist"<<endl;
        return SQL_ACCOUNT_NOT_REGISTED;
    }
    if(check_Online(&db,contact)){
        return SQL_ACCOUNT_ONLINE;
    }else{//缓存申请记录
        char query[250];
        sprintf(query,"insert into message(from_account,to_account,add_flag) values('%s','%s','%d')",account,contact,1);
        if(mysql_query(db.mysql,query)){
            cerr<<"db-Before_Add_Contact:insert error:"<<mysql_error(db.mysql)<<endl;
            exit(-1);
        }
        return SQL_BUFFER_ADD_CONTACT;

    }
}

//after check add contact,return values:
//SQL_FALSE / SQL_TRUE
int Add_Contact(DB db,const char *account,const char *contact){
    if(!get_Connection(&db)){
        exit(-1);
    }
    string account_name=getName_by_account(&db,account);
    string contact_name=getName_by_account(&db,contact);
    char query[250];
    char query1[250];
    sprintf(query,"insert into contacts values('%s','%s','%s')",account,contact,contact_name.c_str());
    sprintf(query1,"insert into contacts values('%s','%s','%s')",contact,account,account_name.c_str());
    mysql_autocommit(db.mysql,0);//mysql event
    int ret=mysql_query(db.mysql,query);
    int ret1=mysql_query(db.mysql,query1);
    if(ret==0&&ret1==0){
        mysql_commit(db.mysql);
        return SQL_TRUE;
    }else{
        mysql_rollback(db.mysql);
        return SQL_FALSE;
    }

}
int Set_Nickname(DB db,const char *account,const char *contact,const char *nickname){
    if(!get_Connection(&db)){
        exit(-1);
    }
    char query[250];
    sprintf(query,"update contacts set nickname='%s' where account='%s' and contact='%s'",nickname,account,contact);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Set_Nickname:update error"<<mysql_error(db.mysql)<<endl;
        return SQL_FALSE;
    }else{
        return SQL_TRUE;
    }
}
int Del_Contact(DB db,const char *account,const char *contact){
    if(!get_Connection(&db)){
        exit(-1);
    }
    char query[250];
    char query1[250];
    sprintf(query,"delete from contacts where account='%s' and contact='%s'",account,contact);
    sprintf(query1,"delete from contacts where account='%s' and contact='%s'",contact,account);
    mysql_autocommit(db.mysql,0);
    int ret=mysql_query(db.mysql,query);
    int ret1=mysql_query(db.mysql,query1);
    if(ret==0 && ret1==0){
        mysql_commit(db.mysql);
        return SQL_TRUE;
    }else{
        mysql_rollback(db.mysql);
        return SQL_FALSE;
    }

}
vector<string> Get_Contact_List(DB db,const char *account){
    if(!get_Connection(&db)){
        exit(-1);
    }
    char query[250];
    sprintf(query,"select nickname from contacts where account='%s'",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Get_Contact_List:select error"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Get_Contact_List:mysql store result error:"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    MYSQL_ROW row;
    vector<string> contact_list;
    while((row=mysql_fetch_row(res))!=NULL){
        contact_list.push_back(row[0]);
    }
    mysql_free_result(res);
    return contact_list;
}
//===============message==========

//before send message,return values:
//SQL_ACCOUNT_ONLINE
//SQL_BUFFER_SEND_MESSAGE
int Before_Send_Message(DB db,const char *from_account,const char *to_account,const char *message){
    if(!get_Connection(&db)){
        exit(-1);
    }
    if(check_Online(&db,to_account)){
        return SQL_ACCOUNT_ONLINE;
    }else{
        char query[1250];
        sprintf(query,"insert into message(from_account,to_account,message_data,buffer_status) values('%s','%s','%s','%d')",from_account,to_account,message,1);
        if(mysql_query(db.mysql,query)){
            cerr<<"db-Before_Send_Message:insert error"<<mysql_error(db.mysql)<<endl;
            exit(-1);
        }
        return SQL_BUFFER_SEND_MESSAGE;
    }
}
// int Get_New_Contact(DB db,const char *account,const char *contact){
//     if(!get_Connection(&db)){
//         exit(-1);
//     }
//     if(Check_Add_Flag(&db,account)){

//     }
// }

// string Get_Message_Buffer(DB db,const char *account){

// }