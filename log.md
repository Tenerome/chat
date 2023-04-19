### 总体架构

即时通信系统是一个复杂的系统，需要考虑到诸多因素，如通信协议、用户界面、网络连接、数据传输等等。以下是一些基本的步骤：

1. 选择通信协议：即时通信系统需要选择一个合适的通信协议，如TCP、UDP等。TCP协议可靠但速度较慢，UDP协议速度快但不可靠。需要根据实际需求选择合适的协议。

2. 设计用户界面：即时通信系统需要一个友好的用户界面，包括登录界面、联系人列表、聊天窗口等等。需要根据用户需求设计符合用户习惯的界面。

3. 建立网络连接：即时通信系统需要建立网络连接，可以通过socket编程实现。

4. 实现数据传输：即时通信系统需要实现数据传输，包括文字、图片、音频、视频等等。需要考虑数据传输的速度和稳定性。

5. 实现聊天功能：即时通信系统的核心功能是聊天，需要实现聊天功能，包括文字聊天、语音聊天、视频聊天等等。需要考虑到聊天的实时性和质量。

6. 实现其他功能：即时通信系统还可以实现一些其他的功能，如文件传输、群聊、表情包、消息提醒等等。

### 逻辑分层设计

1. 用户界面层：这一层主要负责用户交互，包括登录、注册、添加好友、查看聊天记录、发送消息等操作。可以使用 GUI 库（如Qt、MFC、WinForm等）来实现。

2. 逻辑层：这一层主要负责业务逻辑的处理，包括消息的发送和接收、好友的管理、聊天记录的存储、好友在线状态的维护等。可以使用 C++ 来实现。

3. 网络层：这一层主要负责网络通信的处理，包括建立连接、传输数据等操作。可以使用 socket 编程来实现。

4. 数据库层：这一层主要负责数据的存储和管理，包括用户信息、好友列表、聊天记录等。可以使用 MySQL、SQLite 等数据库来实现。

5. 第三方服务层：这一层主要负责第三方服务的集成，如推送服务、文件存储服务等。

### 工作流程

这个系统的工作流程如下：

1. 用户在客户端登录，客户端向服务器发送登录请求。

2. 服务器接收到登录请求，验证用户身份，并返回登录结果和好友列表等信息。

3. 用户在客户端可以查看好友列表，添加好友等操作，修改后会将好友列表信息更新到服务器。

4. 用户可以选择好友进行聊天，客户端向服务器发送聊天请求。

5. 服务器接收到聊天请求，将消息发送给对应的好友。

6. 好友收到消息后，客户端会弹出一个聊天窗口，用户可以在聊天窗口中进行聊天。

7. 聊天过程中，消息会被保存到服务器上，以便用户下次登录查看聊天记录。

8. 用户退出客户端时，客户端会向服务器发送退出请求，服务器会将用户从在线列表中移除

### 消息格式设计

1. 文本消息格式：一般采用纯文本格式，即将文本消息转换为字符串进行传输，接收方收到消息后直接显示字符串内容。

2. 图片消息格式：一般采用二进制格式，即将图片转换为二进制流进行传输，接收方收到消息后将二进制流转换为图片进行显示。

3. 音频消息格式：一般采用音频格式，如mp3、wav等，将音频数据以二进制流形式进行传输，接收方收到消息后将音频数据解码并播放。

4. 视频消息格式：一般采用视频格式，如mp4、avi等，将视频数据以二进制流形式进行传输，接收方收到消息后将视频数据解码并播放。

在实际开发中，还可以根据实际需求和数据类型，自定义消息格式。需要注意的是，消息格式的设计需要充分考虑到数据的传输速度和稳定性，避免消息传输过程中出现丢包、延迟等问题。

### 信令系统

0：注册 1：登陆 2：下线(主动) 3：发信息 4：添加好友 5：删除好友 6：备注好友

```cpp
#define SINGAL_LOGUP 0
#define SIGNAL_LOGIN 1
...
```

### 结构体

#### 信令结构体

```cpp
struct signal{
    unsigned int signal:4;
}
```

4位二进制，16个状态

#### user：注册、登陆、下线

```cpp
struct user{
    user_id;
    event_flag; 
    user_status;   
}
```

#### message:

```cpp
struct message{
    from;
    to;
    message_data;
    message_type;
}
```

#### friend:添加好友、删除好友、备注好友

```cpp
struct friend{
    user;
    firend;
    event_flag;
}
```

### 数据库

#### 采用docker部署数据库

安装docker

pull mysql

```docker
sudo docker run -p 3306:3306 --name mysql -v /home/docker/mysql/logs:/logs -v /home/docker/mysql/data:/mysql_data -e MYSQL_ROOT_PASSWORD=123456 -d mysql
```

docker start

```cpp
sudo docker start mysql
```

#### ~~使用mysql connector C++~~使用sqlapi++

sqlapi++:https://www.sqlapi.com/

下载linux Trial Version

选取头文件:myAPI.h, samisc.h, SQLAPI.h, mysql/*

库文件:

首先`g++ --version` ,`uname -a`->选binaries g++ 10 amd64

添加到ld.conf`sudo vim ld.so.conf`;`sudo ldconfig`;

编译的时候添加库路径`g++ -L../lib -lsqlapi`

#### 数据库表结构

创建user表

```sql
    uid int auto_increment NOT NULL,
    account varchar(100) NOT NULL,
    password varchar(100) NOT NULL,
    name varchar(100) NULL,
    status BOOL NULL,
    route varchar(100) NULL,
    CONSTRAINT user_PK PRIMARY KEY (uid)
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8mb4
COLLATE=utf8mb4_0900_ai_ci;
```

### 安全与验证

#### 用户密码

用户密码不采用明文，使用md5算法，加密字符串密码后再存入数据库，验证密码只需对比md5值。

C++ md5算法选用[GitHub - JieweiWei/md5: 用C++实现md5加密算法](https://github.com/JieweiWei/md5).

加密后得到长度为32的字符串，所以结构体密码变量设置为33。

用户密码加密放在客户端，加密后直接释放内存，让明文密码不出现信息传输中。

#### 格式验证

同样放在客户端，验证输入信息格式是否符合要求

#### 数据库登陆

数据库登陆不采用明文，使用base64加密后存在文件中，文件设置成root用户下，普通用户无法读取，在程序中读取解密传入参数，登陆数据库，整个过程不出现密码明文。

```bash
sudo echo "password"<<pass.dat
sudo chmod -r pass.dat
```

普通用户就没有读权限

base64解密采用[github base64](https://github.com/zhicheng/base64).

```git
git clone https://github.com/zhicheng/base64
```

api:

```cpp
unsigned int
base64_decode(const char *in, unsigned int inlen, unsigned char *out);
```

### 心跳检测

### 设定

- 所有变量用小写字母+数字+下划线表示

- 函数用大小写字母+数字+下划线表示

- 宏和信号量用大写字母+数字+下划线表示

- 所有的错误输出用cerr,结果输出用cout，且输出格式为：文件名+函数名+消息

- bool函数中都按false,false,false...true结构，遇到错误时，输出错误信息，直到最后的true没有任何错误，true不输出信息，交给上层输出。

```cpp
bool fun(){
    if(...){
        cerr<<...;
        return false;
    }
    if(...){
        cerr<<...;
        return false;
    }
    return true;
}
```

遇到异常无需返回值时，用exit()退出

### 内联函数

db中的获取连接和检测用户功能会被多个函数复用，但因为传入的地址，所以可以使用内联函数

### 编译环境

include

task

-I lib,-lmysqlclient

批处理脚本编译

### 问题和难题

###### 字符串越界问题

string和char*的转换中注意边界的'\0',不然可能在读取的时候读到下一个字符串的字节，必要时手动添加`str[strlen[str]]='\0';`

###### C++构造函数调用另一个构造函数

起初使用java那样

```cpp
class myclass{
    myclass(int){myclass(int,0)};
    myclass(int,int);
};
```

结果发现错误，C++不能这么用，检索网络的解决办法是使用new

```cpp
myclass(int){
    new (this)myclass(int,0);
}
```

但是这样没法delete，会导致OOM，segmentation fault

最后在chatgpt中检索，得到委托构造函数，才想起来C++的用法：

```cpp
myclass(int):myclass(int,0){}
```

##### memset等操作内存的函数不要乱用

参考：[内存越界：corrupted double-linked list - gelon - 博客园](https://www.cnblogs.com/gelon/p/13042583.html)

###### C++函数不能返回地址

函数的空间属于栈空间，在函数结束时被释放掉，所以函数内申请的空间都无法返回。想要得到函数内的地址相关的信息，可以传入指针进去，或者在函数中用new，malloc申请空间，申请的是堆内存，但一定要对应的delete和free，不然会OOM

###### 缺省参数

函数的缺省参数声明和定义中只能有一个，不能同时都有

###### if...else中的return

当return 放在if...else结构中时，要保证所有的函数的返回值的可达性。如

```cpp
int fun(...){
    if(...){
        return 0;
    }
}
```

如果条件否，那么就没有返回值。
