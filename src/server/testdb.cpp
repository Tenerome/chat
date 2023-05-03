#include<iostream>
#include "json.hpp"

using json=nlohmann::json;
int main(){
    //json to string
    json j;
    j["acount"]="a76326350";
    j["password"]="zxcvbnmasdfghjklqwertyuiop123456";
    std::string json_string=j.dump();
    std::cout<<json_string<<"  ";
    //string to json
    json_string="{\"name\":\"Zhouqi\",\"sex\":\"man\"}";
    json J=json::parse(json_string);
    std::string name=J["name"];
    std::string sex=J["sex"];
    std::cout<<name<<" "<<sex<<" ";

}