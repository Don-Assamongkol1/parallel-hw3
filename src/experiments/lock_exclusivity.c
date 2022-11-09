#include "CS_exclusivity.h"
#define TARGET 1000

typedef struct _thread_args_t {
    volatile int* counter_ref;
    int thread_idx;
    lock_t* lock;
    int* num_threads_in_CS;
} thread_args_t;

void* thr_func(void* input) {
    thread_args_t* thr_args = (thread_args_t*)input;
    volatile int* counter_ref = thr_args->counter_ref;
    lock_t* lock = thr_args->lock;
    int thread_idx = thr_args->thread_idx;
    int* num_threads_in_CS = thr_args->num_threads_in_CS;

    while (*counter_ref < TARGET) {
        lock_lock(lock, thread_idx);
        *num_threads_in_CS += 1;
        if (*counter_ref < TARGET) {
            *counter_ref += 1;  // check that another thread has not already incremented counter to the desired val
        }
        usleep(100 * 1);  // sleep to increase chance of interrupts
        *num_threads_in_CS -= 1;
        lock_unlock(lock, thread_idx);
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
    lock->numThreads = numThreads;

    volatile int counter = 0;

    /* Start of experiment */
    lock_init(lock);

    /* Spawn our threads */
    thread_args_t thr_args[numThreads];  // must memory allocate the arg to each thread
    pthread_t thread_ids[numThreads];    // so we can keep track of our threads
    int num_threads_in_CS = 0;

    for (int i = 0; i < numThreads; i++) {
        thr_args[i].counter_ref = &counter;
        thr_args[i].lock = lock;
        thr_args[i].thread_idx = i;
        thr_args[i].num_threads_in_CS = &num_threads_in_CS;

        if (pthread_create(&(thread_ids[i]), NULL, &thr_func, (void*)&thr_args[i]) != 0) {
            printf("error creating thread!\n");
            return 1;
        }
    }

    /* Wait here for our threads to join */
    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(thread_ids[i], NULL) != 0) {
            printf("error joining thread!\n");
            return 1;
        }
    }

    printf("done!\n");

    lock_destroy(lock);
}