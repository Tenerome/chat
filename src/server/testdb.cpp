#include<db.h>
#include<vector>
int main(){
    DB db("123456");
    vector<string> contact_list=Get_Contact_List(db,"test123");
    for(auto it=contact_list.begin();it!=contact_list.end();++it){
        cout<<*it<<"  ";
    }
    
}