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
// string Get_Message_Buffer(DB &db,const char *account){

// }