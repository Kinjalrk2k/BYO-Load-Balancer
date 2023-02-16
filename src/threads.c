#include "../include/threads.h"

/**
 * @brief create the thread pool for handling requests
 *
 */
void init_thread_pool() {
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_handler, NULL);
    }
}