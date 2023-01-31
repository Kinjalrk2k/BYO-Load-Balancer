#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

#include "./connection.h"

#define THREAD_POOL_SIZE 5

pthread_t thread_pool[THREAD_POOL_SIZE];

void init_thread_pool();

#endif  // THREADS_H