#include "send_file.h"
#include <my_header.h>

void send_file(int fd){
    
    char *file_name = "THE_HOLY_BIBLE.txt";

    int file_fd = open(file_name,O_RDWR);

    struct stat st;
    fstat(file_fd,&st);
    off_t file_len = st.st_size;

    int len = strlen(file_name);
    send(fd,&len,sizeof(int),MSG_NOSIGNAL);
    send(fd,file_name,len,MSG_NOSIGNAL);

    send(fd, &file_len,sizeof(off_t), MSG_NOSIGNAL);
    sendfile(fd,file_fd,NULL,file_len);

    close(file_fd);
}
