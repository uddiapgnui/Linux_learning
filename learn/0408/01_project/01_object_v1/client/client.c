#include <my_header.h>

int main(int argc, char *argv[]){

    char *ip = "172.16.55.98";
    char *port = "12345";

    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listen_fd,-1,"socket");

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);

    int ret = connect(listen_fd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");

    char buf[100] = {0};
    int cnt = recv(listen_fd,buf,sizeof(buf),0);
    
    printf("recv cnt: %d\n",cnt);
    printf("client buf: %s\n",buf);
    close(listen_fd);
    return 0;
}
