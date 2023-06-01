#include <db.h>

//Send Add Contact Request:return values:
//SQL_ACCOUNT_NOT_REGISTED
//SQL_ACCOUNT_ONLINE
//SQL_BUFFER_ADD_CONTACT
int Send_Add_Contact_Request(DB &db,const char *account,const char *contact){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    if(!check_Existed(db,contact)){
        cout<<contact<<"does not exist"<<endl;
        mysql_close(db.mysql);
        return SQL_ACCOUNT_NOT_REGISTED;
    }
    if(check_Online(db,contact)){
        mysql_close(db.mysql);
        return SQL_ACCOUNT_ONLINE;
    }else{//buffer
        char query[250];
        sprintf(query,"insert into message(from_account,to_account,add_flag) values('%s','%s','%d')",account,contact,1);
        if(mysql_query(db.mysql,query)){
            cerr<<"db-Send_Add_Contact_Request:insert error:"<<mysql_error(db.mysql)<<endl;
            // raise(SIGINT);
            throw ERROR_SQL_QUERY;
            return -1;
        }
        mysql_close(db.mysql);
        return SQL_BUFFER_ADD_CONTACT;

    }
}

//answer add contact request,return values:
//SQL_ACCOUNT_ONLINE
//SQL_BUFFER_ADD_CONTACT
int Answer_Add_Contact(DB &db,const char *account,const char *contact,int answer){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    if(check_Online(db,contact)){
        mysql_close(db.mysql);
        return SQL_ACCOUNT_ONLINE;
    }else{//buffer
        char query[250];
        sprintf(query,"insert into message(from_account,to_account,answer_add) values('%s','%s','%d')",contact,account,answer);
        if(mysql_query(db.mysql,query)){
            cerr<<"db-Before_Add_Contact:insert error:"<<mysql_error(db.mysql)<<endl;
            // raise(SIGINT);
            throw ERROR_SQL_QUERY;
            return -1;
        }
        mysql_close(db.mysql);
        return SQL_BUFFER_ADD_CONTACT;
    }
}

//after check add contact,return values:
//SQL_FALSE / SQL_TRUE
int Add_Contact(DB &db,const char *account,const char *contact){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    string account_name=getName_by_account(db,account);
    string contact_name=getName_by_account(db,contact);
    char query[250];
    char query1[250];
    sprintf(query,"insert into contacts values('%s','%s','%s')",account,contact,contact_name.c_str());
    sprintf(query1,"insert into contacts values('%s','%s','%s')",contact,account,account_name.c_str());
    mysql_autocommit(db.mysql,0);//mysql event
    int ret=mysql_query(db.mysql,query);
    int ret1=mysql_query(db.mysql,query1);
    if(ret==0&&ret1==0){
        mysql_commit(db.mysql);
        mysql_close(db.mysql);
        return SQL_TRUE;
    }else{
        mysql_rollback(db.mysql);
        mysql_close(db.mysql);
        return SQL_FALSE;
    }

}
//if true contact_add_list=add list
bool get_Add_Flag(DB &db,const char *account,vector<string> &contact_add_list){//account=to
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    char query[250];
    sprintf(query,"select add_flag,from_account from message where to_account='%s' and add_flag is not null",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Get_Add_Buffer:store result error"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    MYSQL_ROW row;
    try{
        if(mysql_num_rows(res)==0){
            mysql_free_result(res);
            mysql_close(db.mysql);
            return false;
        }else{
            while((row=mysql_fetch_row(res))!=NULL){
                if(strcmp(row[0],"1")==0){
                    contact_add_list.push_back(row[1]);
                }
            }
            mysql_free_result(res);
            //delete buffer
            sprintf(query,"delete from message where to_account='%s' and add_flag=1 ",account);
            if(mysql_query(db.mysql,query)){
                cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db.mysql)<<endl;
                // raise(SIGINT);
                throw ERROR_SQL_QUERY;
                return -1;

            }
            mysql_close(db.mysql);
            return true;
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    //finally
    mysql_close(db.mysql);
    return false;
}
//if true agree_contact=agree list,reject_contact=reject list
bool get_Answer_Add(DB &db,const char *account,vector<string> &agree_contact,vector<string> &reject_contact){//account=from
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    char query[250];
    sprintf(query,"select answer_add,to_account from message where from_account='%s' and answer_add is not null",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Get_Add_Buffer:store result error"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    try{
        if(mysql_num_rows(res)==0){
            mysql_free_result(res);
            mysql_close(db.mysql);
            return false;
        }else{
            MYSQL_ROW row;
            while((row=mysql_fetch_row(res))!=NULL){
                if(strcmp(row[0],"1")==0){
                    agree_contact.push_back(row[1]);
                }else if(strcmp(row[0],"0")==0){
                    reject_contact.push_back(row[1]);
                }else{
                    continue;//no answer
                }
            }
            mysql_free_result(res);
            //del buffer
            sprintf(query,"delete from message where from_account='%s' and answer_add is not null ",account);
            if(mysql_query(db.mysql,query)){
                cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db.mysql)<<endl;
                // raise(SIGINT);
                throw ERROR_SQL_QUERY;
                return -1;
            }
            mysql_close(db.mysql);
            return true;
        }
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    //finally
    mysql_close(db.mysql);
    return false;
}

bool Set_Nickname(DB &db,const char *account,const char *contact,const char *nickname){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    char query[250];
    if(strcmp(account,contact)==0){
        sprintf(query,"update user set name='%s' where account='%s'",nickname,account);

    }else{
        sprintf(query,"update contacts set nickname='%s' where account='%s' and contact='%s'",nickname,account,contact);
    }
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Set_Nickname:update error"<<mysql_error(db.mysql)<<endl;
        mysql_close(db.mysql);
        return false;
    }else{
        mysql_close(db.mysql);
        return true;
    }
}
bool Del_Contact(DB &db,const char *account,const char *contact){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
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
        mysql_close(db.mysql);
        return true;
    }else{
        mysql_rollback(db.mysql);
        mysql_close(db.mysql);
        return false;
    }

}
bool Get_Contact_List(DB &db,const char *account,map<string,string> &contact_list){
    if(!get_Connection(db)){
        // raise(SIGINT);
        throw ERROR_SQL_CONNECTION;
        return -1;
    }
    char query[250];
    sprintf(query,"select contact,nickname from contacts where account='%s'",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Get_Contact_List:select error"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_QUERY;
        return -1;
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Get_Contact_List:mysql store result error:"<<mysql_error(db.mysql)<<endl;
        // raise(SIGINT);
        throw ERROR_SQL_RES_NULL;
        return -1;
    }
    if(mysql_num_rows(res)==0){
        mysql_free_result(res);
        mysql_close(db.mysql);
        return false;
    }else{
        MYSQL_ROW row;
        while((row=mysql_fetch_row(res))!=NULL){
            contact_list.insert(pair<string,string>(row[0],row[1]));
        }
        mysql_free_result(res);
        mysql_close(db.mysql);
        return true;
    }
}
