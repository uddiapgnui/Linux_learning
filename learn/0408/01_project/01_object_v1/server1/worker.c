#include "worker.h"
#include "queue.h"
#include "thread_pool.h"
#include "send_file.h"

void *thread_func(void *arg){

    thread_pool_t *pool = (thread_pool_t *)arg;

    while(1){

        pthread_mutex_lock(&pool->lock);

        while(pool->queue.size == 0){
            pthread_cond_wait(&pool->cond,&pool->lock);
        }

        int fd = pool->queue.head->fd;

        deQueue(&pool->queue);

        pthread_mutex_unlock(&pool->lock);

        send_file(fd);
        close(fd);
    }

    return NULL;
}
