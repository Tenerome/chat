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

### Display
1. format checking  
![image](https://github.com/Tenerome/chat/assets/62417287/524a0183-fc8d-4d2a-ac78-04cbf3e82cc8)  
![image](https://github.com/Tenerome/chat/assets/62417287/e5e256ad-9ef1-4cd1-abaa-0548fececc0f)  
![image](https://github.com/Tenerome/chat/assets/62417287/6b53d5e4-5b51-4b59-8230-318253dc08f6)
2. chatting  
![image](https://github.com/Tenerome/chat/assets/62417287/b4c3f39a-f7d9-4f9f-ac3a-d35a02ed4b70)
![image](https://github.com/Tenerome/chat/assets/62417287/b0050987-1aa4-4809-939a-797a45266022)
![image](https://github.com/Tenerome/chat/assets/62417287/f6050a07-d449-4d6e-882c-690a5f065127)
3. settings  
![image](https://github.com/Tenerome/chat/assets/62417287/ccf8465f-d903-483d-a727-74740822d487)
4. multi platform  
![image](https://github.com/Tenerome/chat/assets/62417287/9ffdccaf-1b63-4fb2-8a07-11bcb40710af)
5. others  
![image](https://github.com/Tenerome/chat/assets/62417287/44cec885-8398-4669-9738-280a8f67e67e)  
![image](https://github.com/Tenerome/chat/assets/62417287/57cbdc09-f6a5-45c7-8d63-de7bebb68dcc)  
![image](https://github.com/Tenerome/chat/assets/62417287/f9612c05-5829-4337-9358-1cee86dd068b)  
![image](https://github.com/Tenerome/chat/assets/62417287/0f055596-90fb-44a7-bacc-443fde839b78)  
![image](https://github.com/Tenerome/chat/assets/62417287/0cacf182-f2c0-47b8-b7d4-b413a27a0e33)  



