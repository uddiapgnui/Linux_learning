#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "queue.h"
#include <my_header.h>


typedef struct thread_pool{

    int thread_num;

    pthread_t *thread_id_arr;

    queue_t queue;

    pthread_mutex_t lock;

    pthread_cond_t cond;

}thread_pool_t;

void init_thread_pool(thread_pool_t *pool,int num);

#endif

