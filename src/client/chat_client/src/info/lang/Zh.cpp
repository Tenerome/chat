#include "Zh.h"

Zh::Zh(QObject *parent)
    : Lang{parent}
{
    setObjectName("Zh");
    //log
    login("登陆");
    logup("注册");
    back_login("返回登陆");
    //main
    chat("聊");
    online(" 在线");
    profile("个人");
    add_contact("添加联系人");
    contacts("联系表");
    chatroom("聊天室");
    settings("设置");
    flush("刷新");
    confirm("确认");
    cancel("取消");
    //profile page
    uid("编号");
    name("昵称");
    set_name("修改昵称");
    //add page
    add("添加");
    clear_history("清空记录");
    //settings page
    opacity("透明度");
    darkmode("暗黑模式");
    system("跟随系统");
    light("亮白");
    dark("暗黑");
    locale("语言环境");
    //pop menu
    edit_nickname("修改昵称");
    delete_contact("删除好友");
    download("下载");
    //tips
    account_not_exist("账户不存在");
    account_exist("账户已经存在");
    wrong_password("密码错误");
    input_account("输入账户");
    input_password("输入密码");
    input_name("输入昵称");
    account_short("账户长度太短");
    password_short("密码长度太短");
    name_short("昵称太短");
    logup_succeed("注册成功");
    login_succeed("登陆成功");
    same_password("两次密码需相同");
    clear_message_history("成功清除聊天记录");
    //format
    account_format("8-10位数字");
    password_format("前两位字母+6-8位数字");
    name_format("5-10 个字符");
    //system dialog tray
    quit("退出");
    mini("最小化");
    retry("重试");
}
