#include"db.h"

//before send message,return values:
//SQL_ACCOUNT_ONLINE
//SQL_BUFFER_SEND_MESSAGE
int Before_Send_Message(DB &db,const char *from_account,const char *to_account,const char *message){
    if(!get_Connection(db)){
        exit(-1);
    }
    if(check_Online(db,to_account)){
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
// int Get_New_Contact(DB &db,const char *account,const char *contact){
//     if(!get_Connection(db)){
//         exit(-1);
//     }
//     if(Check_Add_Flag(db,account)){

//     }
// }

// string Get_Message_Buffer(DB &db,const char *account){

// }