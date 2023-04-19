#include "client.h"
int main(){
    int server_socket=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port=htons(8888);
    if(connect(server_socket,(sockaddr*)&server_addr,sizeof(server_addr))==0){
        cout<<"chat: main: connected to server socket"<<endl;
    }else{
        cerr<<"chat: main: failed to connect socket"<<endl;
        exit(-1);
    }
    char account[8]={'\0'};
    char password[20]={'\0'};
    char name[18]={'\0'};
    //TODO 格式验证
    cout<<"input account: ";
    cin>>account;
    // if(account[8]!='\0'){
    //     cerr<<"最大账户长度为8"<<endl;
    //     exit(-1);
    // }
    cout<<"input password: ";
    cin>>password;
    // if(password[20]!='\0'){
    //     cerr<<"最大密码长度为20"<<endl;
    //     exit(-1);
    // }
    cout<<"input name: ";
    cin>>name;
    // if(name[18]!='\0'){
    //     cerr<<"最大长度为6个汉字或18个字母加数字"<<endl;
    //     exit(-1);
    // }
    string en_pass=MD5(password).toStr();//加密
    //录入结构体
    user_Property *user_pro=(user_Property*)malloc(USER_PROPERTY_SIZE);
    strcpy(user_pro->account,account);
    strcpy(user_pro->password,en_pass.c_str());
    strcpy(user_pro->name,name);
    //转入buff
    char *buff=(char*)malloc(USER_PROPERTY_SIZE);//memset 两个空间大小需相同
    memcpy(buff,user_pro,USER_PROPERTY_SIZE);
    send(server_socket,buff,USER_PROPERTY_SIZE,0);
    free(user_pro);
    free(buff);
}