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

    int file_name_len = 0;
    recv(listen_fd,&file_name_len,sizeof(int),MSG_WAITALL);

    char file_name[60] = {0};
    
    off_t file_size = 0;

    recv(listen_fd, &file_size,sizeof(off_t),MSG_WAITALL);
    printf("file_size: %ld \n",file_size);

    int file_fd = open(file_name, O_RDWR | O_CREAT,0600);

    ftruncate(file_fd,file_size);

    char *p = (char *)mmap(NULL,file_size,PROT_READ|PROT_WRITE,MAP_SHARED,file_fd,0);

    munmap(p, file_size);
    close(file_fd);
    close(listen_fd);

    return 0;
}

