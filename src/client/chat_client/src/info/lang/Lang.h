#ifndef LANG_H
#define LANG_H

#include <QObject>
#include "../stdafx.h"

class Lang : public QObject
{
    Q_OBJECT
    //log
    Q_PROPERTY_AUTO(QString,login);
    Q_PROPERTY_AUTO(QString,logup);
    Q_PROPERTY_AUTO(QString,back_login);
    //main
    Q_PROPERTY_AUTO(QString,chat);
    Q_PROPERTY_AUTO(QString,online);
    Q_PROPERTY_AUTO(QString,profile);
    Q_PROPERTY_AUTO(QString,add_contact);
    Q_PROPERTY_AUTO(QString,contacts);
    Q_PROPERTY_AUTO(QString,chatroom);
    Q_PROPERTY_AUTO(QString,settings);
    Q_PROPERTY_AUTO(QString,flush);
    Q_PROPERTY_AUTO(QString,confirm);
    Q_PROPERTY_AUTO(QString,cancel);
    //profile page
    Q_PROPERTY_AUTO(QString,uid);
    Q_PROPERTY_AUTO(QString,name);
    Q_PROPERTY_AUTO(QString,set_name);
    //add page
    Q_PROPERTY_AUTO(QString,add);
    Q_PROPERTY_AUTO(QString,clear_message_history);
    //settings page
    Q_PROPERTY_AUTO(QString,opacity);
    Q_PROPERTY_AUTO(QString,darkmode);
    Q_PROPERTY_AUTO(QString,system);
    Q_PROPERTY_AUTO(QString,light);
    Q_PROPERTY_AUTO(QString,dark);
    Q_PROPERTY_AUTO(QString,locale);
    //pop menu
    Q_PROPERTY_AUTO(QString,edit_nickname);
    Q_PROPERTY_AUTO(QString,delete_contact);
    Q_PROPERTY_AUTO(QString,download);
    //tips
    Q_PROPERTY_AUTO(QString,account_not_exist);
    Q_PROPERTY_AUTO(QString,account_exist);
    Q_PROPERTY_AUTO(QString,wrong_password);
    Q_PROPERTY_AUTO(QString,input_account);
    Q_PROPERTY_AUTO(QString,input_password);
    Q_PROPERTY_AUTO(QString,input_name);
    Q_PROPERTY_AUTO(QString,account_short);
    Q_PROPERTY_AUTO(QString,password_short);
    Q_PROPERTY_AUTO(QString,name_short);
    Q_PROPERTY_AUTO(QString,logup_succeed);
    Q_PROPERTY_AUTO(QString,login_succeed);
    Q_PROPERTY_AUTO(QString,same_password);
    Q_PROPERTY_AUTO(QString,clear_history);
    //format
    Q_PROPERTY_AUTO(QString,account_format);
    Q_PROPERTY_AUTO(QString,password_format);
    Q_PROPERTY_AUTO(QString,name_format);
    //system dialog and tray
    Q_PROPERTY_AUTO(QString,quit);
    Q_PROPERTY_AUTO(QString,mini);
    Q_PROPERTY_AUTO(QString,retry);
public:
    explicit Lang(QObject *parent = nullptr);

};

#endif // LANG_H
