#include "ob_internal.h"
#include <pthread.h>

/* Global handle table and lock */
HANDLE_ENTRY g_handle_table[HANDLE_TABLE_SIZE];
pthread_mutex_t g_handle_table_lock = PTHREAD_MUTEX_INITIALIZER;

/* Root directory pointer */
OBJECT_HEADER *g_root_directory = NULL;

void ob_init_lock(pthread_mutex_t *mtx) {
    pthread_mutex_init(mtx, NULL);
}

void ob_destroy_lock(pthread_mutex_t *mtx) {
    pthread_mutex_destroy(mtx);
}

