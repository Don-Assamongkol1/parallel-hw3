#include "parallel_scaling.h"

typedef struct _thread_args_t {
    volatile int* counter_ref;
    lock_t* lock;
} thread_args_t;

void* thr_func(void* input) {
    thread_args_t* thr_args = (thread_args_t*)input;
    volatile int* counter_ref = thr_args->counter_ref;
    lock_t* lock = thr_args->lock;

    while (*counter_ref < BIG) {
        lock_lock(lock);
        if (*counter_ref < BIG) {
            *counter_ref += 1;  // check that another thread has not already incremented counter to the desired val
        }
        lock_unlock(lock);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error! Please feed in a desired lock type and thread count\n");
        return 0;
    }

    lock_t* lock = malloc(sizeof(lock_t));

    char desired_lock_type = argv[1][0];
    switch (desired_lock_type) {
        case 'T':
            lock->locktype = TAS_LOCK_TYPE;
            break;
        case 'P':
            lock->locktype = PTHREAD_LOCK_TYPE;
            break;
        case 'A':
            lock->locktype = A_LOCK_TYPE;
            break;
        case 'M':
            lock->locktype = TTAS_LOCK_TYPE;
            break;
        default:
            printf("Error! Got an unexpected lock type!\n");
            return 1;
    }
    int numThreads = atoi(argv[2]);

    volatile int counter = 0;
    lock_init(lock);

    /* Spawn our threads */
    thread_args_t thr_args[numThreads];  // must memory allocate the arg to each thread
    pthread_t thread_ids[numThreads];    // so we can keep track of our threads
    for (int i = 0; i < numThreads; i++) {
        thr_args[i].counter_ref = &counter;
        thr_args[i].lock = lock;

        if (pthread_create(&(thread_ids[i]), NULL, &thr_func, (void*)&thr_args[i]) != 0) {
            printf("error creating thread!\n");
            return 1;
        }
    }

    /* Join our threads */
    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(thread_ids[i], NULL) != 0) {
            printf("error joining thread!\n");
            return 1;
        }
    }

    printf("counter: %d\n", counter);

    lock_destroy(lock);
}