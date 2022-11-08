#include "lock.h"

void lock_init(lock_t* lock) {
    lock->lock = malloc(sizeof(__lock_t));

    if (lock->locktype == TAS_LOCK_TYPE) {
        lock->lock->tas_lock = malloc(sizeof(tas_lock_t));  // why is this needed
        tas_lock_init(lock->lock->tas_lock);

    } else if (lock->locktype == PTHREAD_LOCK_TYPE) {
        lock->lock->pthread_lock = malloc(sizeof(pthread_lock_t));
        pthread_lock_init(lock->lock->pthread_lock);

    } else if (lock->locktype == A_LOCK_TYPE) {
        lock->lock->a_lock = malloc(sizeof(a_lock_t));
        lock->lock->a_lock->size = lock->numThreads;

        a_lock_init(lock->lock->a_lock);

    } else if (lock->locktype == TTAS_LOCK_TYPE) {
        lock->lock->ttas_lock = malloc(sizeof(ttas_lock_t));
        ttas_lock_init(lock->lock->ttas_lock);
    }
}

void lock_lock(lock_t* lock, int threadID) {
    if (lock->locktype == TAS_LOCK_TYPE) {
        tas_lock_lock(lock->lock->tas_lock);

    } else if (lock->locktype == PTHREAD_LOCK_TYPE) {
        pthread_lock_lock(lock->lock->pthread_lock);

    } else if (lock->locktype == A_LOCK_TYPE) {
        a_lock_lock(lock->lock->a_lock, threadID);

    } else if (lock->locktype == TTAS_LOCK_TYPE) {
        ttas_lock_lock(lock->lock->ttas_lock);
    }
}

void lock_unlock(lock_t* lock, int threadID) {
    if (lock->locktype == TAS_LOCK_TYPE) {
        tas_lock_unlock(lock->lock->tas_lock);

    } else if (lock->locktype == PTHREAD_LOCK_TYPE) {
        pthread_lock_unlock(lock->lock->pthread_lock);

    } else if (lock->locktype == A_LOCK_TYPE) {
        a_lock_unlock(lock->lock->a_lock, threadID);

    } else if (lock->locktype == TTAS_LOCK_TYPE) {
        ttas_lock_unlock(lock->lock->ttas_lock);
    }
}

void lock_destroy(lock_t* lock) {
    if (lock->locktype == TAS_LOCK_TYPE) {
        tas_lock_destroy(lock->lock->tas_lock);
        free(lock->lock->tas_lock);

    } else if (lock->locktype == PTHREAD_LOCK_TYPE) {
        pthread_lock_destroy(lock->lock->pthread_lock);
        free(lock->lock->pthread_lock);

    } else if (lock->locktype == A_LOCK_TYPE) {
        a_lock_destroy(lock->lock->a_lock);
        free(lock->lock->a_lock);

    } else if (lock->locktype == TTAS_LOCK_TYPE) {
        ttas_lock_destroy(lock->lock->ttas_lock);
        free(lock->lock->ttas_lock);
    }

    free(lock->lock);
    free(lock);
}