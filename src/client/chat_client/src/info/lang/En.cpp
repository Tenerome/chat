#include "En.h"

En::En(QObject *parent)
    : Lang{parent}
{
    setObjectName("En");
    //log
    login("log in");
    logup("log up");
    back_login("back log in");
    //main
    chat("chat");
    online(" online");
    profile("Profile");
    add_contact("Add Contact");
    contacts("Contacts");
    chatroom("Chat Room");
    settings("Settings");
    flush("Flush");
    confirm("confirm");
    cancel("cancel");
    //profile page
    uid("uid");
    name("name");
    set_name("set name");
    //add page
    add("add");
    clear_history("clear history");
    //settings page
    opacity("opacity");
    darkmode("Dark Mode");
    system("system");
    light("light");
    dark("dark");
    locale("Locale");
    //pop menu
    edit_nickname("edit nickname");
    delete_contact("delete contact");
    download("download");
    //tips
    account_not_exist("account does not exist");
    account_exist("account has been existed");
    wrong_password("password is wrong");
    input_account("Input account");
    input_password("Input password");
    input_name("Input name");
    account_short("account is too short");
    password_short("password is too short");
    name_short("name is too short");
    logup_succeed("log up succeed");
    login_succeed("log in succeed");
    same_password("the two passwords must be same");
    clear_message_history("clear message history succeed");
    //format
    account_format("8-10 numbers");
    password_format("tow letters with 6-8 numbers");
    name_format("5-10 letters");
    //system dialog tray
    quit("quit");
    mini("minimal");
    retry("retry");
}
