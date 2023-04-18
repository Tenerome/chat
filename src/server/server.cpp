#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<ctype.h>

#define OPEN_MAX 1024

int main(){
    int i, listenfd, connfd, sockfd,epfd, res, n;
    ssize_t nready = 0;
    char buf[BUFSIZ] = {0};
    char str[INET_ADDRSTRLEN];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event event, events[OPEN_MAX];

    //开始创建服务端套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 128);

    //开始初始化epoll
    epfd = epoll_create(OPEN_MAX);

    event.events = EPOLLIN;
    event.data.fd = listenfd;
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);
    if (res == -1) {
        perror("server epoll_ctl error");
        exit(res);
    }
    
    for(;;) {
        //开始监听
        nready = epoll_wait(epfd, events, OPEN_MAX, -1);
        if (nready == -1) {
            perror("epoll_wait error");
            exit(nready);
        }

        for (i = 0; i < nready; i++) {
            if (!(events[i].events & EPOLLIN)) {
                continue;
            }
            if (events[i].data.fd == listenfd) {
                //有新客户端连接
                clilen = sizeof(cliaddr);
                connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
                printf("received from %s at port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                    ntohs(cliaddr.sin_port));

                event.events = EPOLLIN;
                event.data.fd = connfd;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event) == -1) {
                    perror("client epoll_ctl error");
                    exit(-1);
                }
            } else {
                //有数据可以读取
                sockfd = events[i].data.fd;
                n = read(sockfd, buf, sizeof(buf));
                if (n ==0) {
                    //读到0，说明客户端关闭
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                } else if (n < 0){
                    //出错
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    close(sockfd);
                    printf("client[%d] read error\n", sockfd);
                } else {
                    //读到了数据
                    printf("received data: %s\n", buf);
                }
            }
        }
    }
    close(listenfd);
    close(epfd);
     
    return 0;
}

