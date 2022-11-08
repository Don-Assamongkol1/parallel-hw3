#include "pthread_lock.h"

bool pthread_lock_init(pthread_lock_t* pthread_lock) {
    pthread_lock->mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(pthread_lock->mutex, NULL);
    return true;
}

bool pthread_lock_lock(pthread_lock_t* pthread_lock) {
    pthread_mutex_lock(pthread_lock->mutex);
    return true;
}

bool pthread_lock_unlock(pthread_lock_t* pthread_lock) {
    pthread_mutex_unlock(pthread_lock->mutex);
    return true;
}

bool pthread_lock_destroy(pthread_lock_t* pthread_lock) {
    pthread_mutex_destroy(pthread_lock->mutex);
    return true;
}