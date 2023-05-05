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

### 各层的业务逻辑

#### 登入系统

##### 注册与登陆

1. 用户进入登陆页面，显示登陆窗口
2. 输入账户密码登陆
3. 如果账户不存在，点击注册页面注册
4. 密码正确登陆成功，否则登陆失败

#### 好友

##### 添加好友

1. 用户发起添加好友请求，需要提供对方帐号信息。

2. 系统接收到请求后，首先需要验证用户账号是否合法，以及对方账号是否存在。

3. 如果对方账号存在，则需要验证当前用户是否已经和对方成为好友关系。如果已经是好友，则无法重复添加。还需要检验用户是否在线，在线这继续，离线则缓存申请。

4. 如果还不是好友，则系统会向对方发送添加好友请求，对方可以选择同意或拒绝。

5. 如果对方同意添加好友，则系统会在两个用户之间建立好友关系，并通知双方。

6. 如果对方拒绝添加好友，则会提示当前用户添加失败。

### 消息格式设计

1. 文本消息格式：一般采用纯文本格式，即将文本消息转换为字符串进行传输，接收方收到消息后直接显示字符串内容。

2. 图片消息格式：一般采用二进制格式，即将图片转换为二进制流进行传输，接收方收到消息后将二进制流转换为图片进行显示。

3. 音频消息格式：一般采用音频格式，如mp3、wav等，将音频数据以二进制流形式进行传输，接收方收到消息后将音频数据解码并播放。

4. 视频消息格式：一般采用视频格式，如mp4、avi等，将视频数据以二进制流形式进行传输，接收方收到消息后将视频数据解码并播放。

在实际开发中，还可以根据实际需求和数据类型，自定义消息格式。需要注意的是，消息格式的设计需要充分考虑到数据的传输速度和稳定性，避免消息传输过程中出现丢包、延迟等问题。

### 容器

#### vector

#### map

### 线程池

### 信令系统

//TODO
0：注册 1：登陆 2：下线(主动) 3：发信息 4：添加好友 5：删除好友 6：备注好友

```cpp
#define SINGAL_LOGUP 0
#define SIGNAL_LOGIN 1
...
```

### ~~结构体~~（弃用，改用json）

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

### JSON

客户端和服务端通信采用Json格式，服务端选用[nlohmann/json](https://github.com/nlohmann/json) C++库

该json库使用hpp格式，只需要一个头文件json.hpp,不需要一堆头文件、库、依赖：

> - **Trivial integration**. Our whole code consists of a single header file [`json.hpp`](https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp). That's it. No library, no subproject, no dependencies, no complex build system. The class is written in vanilla C++11. All in all, everything should require no adjustment of your compiler flags or project settings.

API:

```cpp
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
```

QML可以直接使用JavaScript的JSON对象。

### 数据库

#### 采用docker部署数据库

安装docker

pull mysql，并映射本地端口，本地目录

```docker
sudo docker run -p 3306:3306 --name mysql -v /home/docker/mysql/logs:/logs -v /home/docker/mysql/data:/mysql_data -e MYSQL_ROOT_PASSWORD=123456 -d mysql
```

docker start

```cpp
sudo docker start mysql
```

#### 使用mysql connector C++

#### 数据库表结构

用户表
用户表是IM系统中最基础的表，记录用户的基本信息，如用户名、密码、昵称、头像等。每个用户都有一个唯一的ID作为主键。

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

好友关系表
好友关系表记录了用户之间的好友关系，包括好友的ID、好友分组、备注等信息。这个表可以使用两个字段来表示好友之间的关系，例如A和B互为好友，则在这个表中会出现两条记录：A的ID和B的ID以及B的ID和A的ID。

好友分组表
好友分组表用于记录用户好友的分组情况，包括分组名称、所属用户ID等信息。每个用户可以创建多个好友分组，将自己的好友进行分类管理。

消息表
消息表用于记录用户之间的聊天记录，包括发送者ID、接收者ID、消息内容、发送时间等信息。这个表可以使用索引加速查询，提高系统的性能。

群组表
群组表用于记录IM系统中的群组信息，包括群组名称、群组ID、群组头像等信息。每个群组可以包含多个成员，每个成员可以有不同的权限和角色。

群组成员表
群组成员表用于记录群组中的成员信息，包括成员ID、所属群组ID、成员角色等信息。每个成员可以有不同的权限和角色，在群组中扮演不同的角色。

### 安全与验证

#### 用户密码

用户密码不采用明文，使用md5算法，加密字符串密码后再存入数据库，验证密码只需对比md5值。

C++ md5算法选用[JieweiWei/md5](https://github.com/JieweiWei/md5).

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

base64解密采用[zhicheng/base64](https://github.com/zhicheng/base64)

```git
git clone https://github.com/zhicheng/base64
```

api:

```cpp
unsigned int
base64_decode(const char *in, unsigned int inlen, unsigned char *out);
```

### ~~心跳检测~~（弃用，改用epoll编程）

本来学了多线程，想用select+thread循环监听socket，但是看到epoll可以从触发方式上改变监听机制，改用epoll

//TODO

### 设定

#### C++

- 所有变量用小写字母+数字+下划线表示

- 函数用大小写字母+数字+下划线表示

- 宏和信号量用大写字母+数字+下划线表示

- 所有的错误输出用cerr,结果输出用cout，且输出格式为：文件名+函数名+消息

- inlien函数只有两种状态返回，成功或者失败。而上层的函数都有可能多个返回值，所以设置成int型，返回值在信令中预定义

```cpp
int log_up(){
    if(...){
        return SIGNAL_REGISTED;
    }
    if(...){
        return SIGNAL_LOGUP_SUCCEED;
    }
}
```

上层的函数通过读取返回值来做出不同的操作

#### QML

id：小写+下划线

Component：大小写+下划线

Signal：大写+下划线

### 内联函数

db中的获取连接和检测用户等功能会被多个函数复用，但因为传入的地址，所以可以使用内联函数

### 编译环境

除了基础GCC库，额外用到的库不依赖系统环境变量，把用到的头文件，库文件找出来放在项目include/,lib/ 目录下，并手动编译动态库，运行时也需要打上库路径

- 编译动态库
  
  ```bash
  g++ a.c b.cpp -fPIC -shared -o libxxx.so
  ```

- 批处理编译
  
  ```bash
  #! /bin/bash
  includepath="-I../include/ -I../include/encode/ -I../include/mysql/"
  libpath="-L../lib/ -lmysqlclient -lencode"
  #运行时lib
  rlibpath="-Wl,-rpath=../lib/"
  g++ chat_server.cpp ../include/db.cpp -o chat_server $includepath $libpath $rlibpath
  echo "compiled chat_server"
  ```

### UI

  qt6

  安装

  配置

  库apt install lib

  创建chat_client qbs 6.2 debug 先运行一次生成chat_client debug

  FluentUI，重新构建

  生成qmltypes

```bash
./qmlplugindump --nonrelatable FluentUI 1.0 /bin > /bin/Fluent/plugin.qmltypes
```

  导入到debug/debug desktop,也就是chat_client 同级目录下，就可以调用模块。同时也有代码提示

### 问题和难题

###### 字符串越界问题

  string和char*的转换中注意边界的'\0',不然可能在读取的时候读到下一个字符串的字节，必要时手动添加`str[strlen[str]]='\0';`

###### C++构造函数调用另一个构造函数

  起初使用java那样

```
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

###### memset等操作内存的函数不要乱用

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
