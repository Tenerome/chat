cmake_minimum_required(VERSION 3.22.1)
project(chat_server LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
#set build path
set(bulid_path ${PROJECT_SOURCE_DIR}/build/)
#set lib output path
set(LIBRARY_OUTPUT_DIRECTORY ${build_path}/lib/)
#set cache path
set(CMAKE_CACHEFILE_DIR ${build_path}/build_cache/)
#set include path
set(include_path ${PROJECT_SOURCE_DIR}/include/)
#import existed libs
link_directories(${PROJECT_SOURCE_DIR}/lib)

#===================configure==================
set(SERVER_PORT 8888)
set(SQL_HOST "127.0.0.1")
set(SQL_USER "root")
set(SQL_DATABASE "chat") 
set(SQL_PORT 3306)
set(SQL_PASS_PATH "/home/tenerome/Documents/chat/src/server/build/pass.dat")
configure_file(${include_path}/db/server.h.in ${include_path}/db/server.h)
#==============================================

#set includes
include_directories(
    ${PROJECT_SOURCE_DIR}/include/db/
    ${PROJECT_SOURCE_DIR}/include/encode/
    ${PROJECT_SOURCE_DIR}/include/mysql/
    ${PROJECT_SOURCE_DIR}/include/tcpserver/
    ${PROJECT_SOURCE_DIR}/include/json/
    ${PROJECT_SOURCE_DIR}/include/threadpool/
)

#build start
message("build chat_server: \n")

#libTcpServer.so
add_library(TcpServer SHARED 
    ./Source/encode/base64.cpp
    ./Source/encode/md5.cpp
    ./Source/db/db_contact.cpp
    ./Source/db/db_global.cpp
    ./Source/db/db_log.cpp
    ./Source/db/db_message.cpp
    ./Source/tcpserver/tcpserver_contact.cpp
    ./Source/tcpserver/tcpserver_global.cpp
    ./Source/tcpserver/tcpserver_log.cpp
    ./Source/tcpserver/tcpserver_message.cpp
)
#set executable object
add_executable(server_main server_main.cpp)
#link libs
target_link_libraries(server_main PUBLIC TcpServer -lmysqlclient)
