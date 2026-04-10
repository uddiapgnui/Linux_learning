#include <asm-generic/socket.h>
#include <my_header.h>
#include "socket.h"

void init_socket(int *fd, char *ip, char *port){
    
    *fd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(fd,-1,"socket");

    int opt = 1;
    setsockopt(*fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);

    int ret = bind(*fd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(*fd,100);
    ERROR_CHECK(ret,-1,"listen");

}
