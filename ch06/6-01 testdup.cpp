#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << argc << std::endl;
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    std::cout << argv[0] << " " << argv[1] << " " << argv[2] << std::endl;

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    std::cout << sock << std::endl;
    assert(sock >= 0);
    

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);
    std::cout << ret << std::endl;
    
    ret = listen(sock, 5);
    assert(ret != -1);
    std::cout << ret << std::endl;

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    std::cout << client_addrlength << std::endl;
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    
    if(connfd < 0){
        printf("errno is: %d\n", errno);
    } else {
        close(STDOUT_FILENO);
        dup(connfd);
        printf("abcd\n");
        close(connfd);
    }
    close(sock);
    return 0;
}
