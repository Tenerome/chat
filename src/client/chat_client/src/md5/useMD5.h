#ifndef USEMD5_H
#define USEMD5_H

#include<QObject>

class useMD5:public QObject{
    Q_OBJECT
public:
    explicit useMD5(QObject *parent=nullptr);
    Q_INVOKABLE QString toStr(QString message);
};


#endif // USEMD5_H
