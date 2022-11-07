#include "parallel_main.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error! Please feed in a desired lock type\n");
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

    StopWatch_t* stopwatch = malloc(sizeof(StopWatch_t));
    startTimer(stopwatch);

    volatile int counter = 0;
    lock_init(lock);
    for (int i = 0; i < BIG; i++) {
        lock_lock(lock);
        counter += 1;
        lock_unlock(lock);
    }
    counter;  // to suppress unused var warning

    stopTimer(stopwatch);
    double elapsed_time = getElapsedTime(stopwatch);
    printf("elapsed_time: %f\n", elapsed_time);
    free(stopwatch);

    lock_destroy(lock);
}