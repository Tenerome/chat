#include"db.h"

//before send message,return values:
//SQL_ACCOUNT_ONLINE
//SQL_BUFFER_SEND_MESSAGE
int Send_Message(DB &db,const char *from_account,const char *to_account,const char *message,int message_type){
    if(!get_Connection(db)){
        exit(-1);
    }
    if(check_Online(db,to_account)){
        mysql_close(db.mysql);
        return SQL_ACCOUNT_ONLINE;
    }else{
        char query[1250];
        sprintf(query,"insert into message(from_account,to_account,message_data,message_buffer) values('%s','%s','%s','%d')",from_account,to_account,message,message_type);
        if(mysql_query(db.mysql,query)){
            cerr<<"db-Before_Send_Message:insert error"<<mysql_error(db.mysql)<<endl;
            exit(-1);
        }
        mysql_close(db.mysql);
        return SQL_BUFFER_SEND_MESSAGE;
    }
}
bool Get_Message_Buffer(DB &db,const char *account,map<string,string> &message_list){
    if(!get_Connection(db)){
        exit(-1);
    }
    char query[250];
    sprintf(query,"select from_account,message_data,message_buffer from message where to_account='%s' and message_buffer=0",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Get_Contact_List:select error"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Get_Contact_List:mysql store result error:"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    if(mysql_num_rows(res)==0){
        mysql_free_result(res);
        mysql_close(db.mysql);
        return false;
    }else{
        MYSQL_ROW row;
        while((row=mysql_fetch_row(res))!=NULL){
            message_list.insert(pair<string,string>(row[0],row[1]));
        }
        mysql_free_result(res);
        //del buff
        sprintf(query,"delete from message where to_account='%s' and message_buffer=0 ",account);
            if(mysql_query(db.mysql,query)){
                cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db.mysql)<<endl;
                exit(-1);
            }
        mysql_close(db.mysql);
        return true;
    }
}
bool Get_Image_Buffer(DB &db,const char *account,map<string,string> &image_list){
    if(!get_Connection(db)){
        exit(-1);
    }
    char query[250];
    sprintf(query,"select from_account,message_data,message_buffer from message where to_account='%s' and message_buffer=1",account);
    if(mysql_query(db.mysql,query)){
        cerr<<"db-Get_Contact_List:select error"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    MYSQL_RES *res=mysql_store_result(db.mysql);
    if(res==NULL){
        cerr<<"db-Get_Contact_List:mysql store result error:"<<mysql_error(db.mysql)<<endl;
        exit(-1);
    }
    if(mysql_num_rows(res)==0){
        mysql_free_result(res);
        mysql_close(db.mysql);
        return false;
    }else{
        MYSQL_ROW row;
        while((row=mysql_fetch_row(res))!=NULL){
            image_list.insert(pair<string,string>(row[0],row[1]));
        }
        mysql_free_result(res);
        //del buffer
        sprintf(query,"delete from message where to_account='%s' and message_buffer=1 ",account);
            if(mysql_query(db.mysql,query)){
                cerr<<"db-Get_Add_Buffer:select error"<<mysql_error(db.mysql)<<endl;
                exit(-1);
            }
        mysql_close(db.mysql);
        return true;
    }
}