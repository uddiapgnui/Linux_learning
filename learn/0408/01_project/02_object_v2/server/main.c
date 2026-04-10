#include "queue.h"
#include "epoll.h"
#include "socket.h"
#include "thread_pool.h"
#include <my_header.h>
#include <sys/epoll.h>

int main(int argc, char *argv[]){

    thread_pool_t pool;
    init_thread_pool(&pool,4);

    int listen_fd = 0;
    init_socket(&listen_fd,"172.16.55.98","12345");

    int epfd = epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");

    add_epoll_fd(epfd,listen_fd);

    while(1){
        struct epoll_event lst[10];
        int nready = epoll_wait(epfd,lst,10,-1);
        ERROR_CHECK(nready,-1,"epoll_wait");
        printf("nready: %d\n",nready);

        for(int idx = 0; idx < nready; ++idx){
            int fd = lst[idx].data.fd;

            if(fd == listen_fd){
                int conn_fd = accept(listen_fd, NULL,NULL);
                ERROR_CHECK(conn_fd,-1,"accept");

                pthread_mutex_lock(&pool.lock);

                enQueue(&pool.queue,conn_fd);

                pthread_cond_signal(&pool.cond);
                pthread_mutex_unlock(&pool.lock);
            }
        }
    }

    return 0;
}

