### chat:A IM System

- client name:chat

- server name:chat_server

- Languages
  
  - Server: C++
  
  - Client: QML with Qt C++

- Environment and Framework
  
  - FluentUI :for client ui
  
  - docker :for mysql server, vsftpd

- build
1. pass.dat

    create the pass.dat file,

    encode the password of mysql user with md5:`md=MD5("password")`

    encode again with base64:`base=base64(md)`

    append "base" to "pass.dat" :`echo base >> pass.dat`

2. CMakeLists.txt

    set the arguments

```cmake
set(SERVER_PORT 8888)
set(SQL_HOST "127.0.0.1")
set(SQL_USER "root")
set(SQL_DATABASE "chat") 
set(SQL_PORT 3306)
set(SQL_PASS_PATH "/home/tenerome/Documents/chat/src/server/build/pass.dat")
```

3. cmake & make

```bash
mkdir /build
cd /build
cmake ..
make
./server_main   
```

- SQL
1. user

| Column Name | Data Type | Length | Key | Auto Increment |
| ----------- | --------- | ------ | --- | -------------- |
| uid         | int       | 128    | PRI | v              |
| account     | varchar   | 128    | UNI |                |
| password    | varchar   | 128    |     |                |
| name        | varchar   | 128    |     |                |
| status      | int       | 1      |     |                |
| route       | int       | 1      |     |                |

2. message

| Column Name    | Data Type | Length | Key |
| -------------- | --------- | ------ | --- |
| from_account   | varchar   | 128    | MUL |
| to_account     | varchar   | 128    | MUL |
| add_flag       | int       | 1      |     |
| answer_flag    | int       | 1      |     |
| message_buffer | int       | 1      |     |
| message_data   | varchar   | 2048   |     |

3. contact

| Column Name | Data Type | Length | Key |
| ----------- | --------- | ------ | --- |
| account     | varchar   | 128    | MUL |
| contact     | varchar   | 128    | MUL |
| nickname    | varchar   | 128    |     |

4. chatroom

| Column Name | Data Type | Length |     |
| ----------- | --------- | ------ | --- |
| account     | varchar   | 128    | MUL |
| message     | varchar   | 128    |     |
