#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool stop = false;

/*SIGTERM信号的处理函数，触发时结束主程序中的循环*/
static void handle_term(int sig){
    stop = true;
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, handle_term);//关闭信号

    if(argc <= 3){
        printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]); //backlog参数提示内核监听队列的最大长度

    int sock = socket(PF_INET, SOCK_STREAM, 0);//ipv4 流服务tcp 默认协议
    assert(sock >= 0);

    /*创建一个IPv4 socket地址*/
    struct sockaddr_in address;
    bzero(&address, sizeof(address));//设置为0
    address.sin_family = AF_INET;//tcp ipv4
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));//自动分配socket地址
    assert(ret != -1);

    ret = listen(sock, backlog);//创建一个监听队列
    assert(ret != -1);
    /*循环等待连接，直到有SIGTERM信号将它中断*/
    while(!stop){
        sleep(1);
    }

    close(sock);
    return 0;
}