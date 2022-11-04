#include "parallel_main.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error! Please feed in a desired lock type\n");
        return 0;
    }

    lock_t* lock = malloc(sizeof(lock_t));

    int desired_lock_type = argv[1][0];
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

    lock_init(lock);
    volatile int counter = 0;
    for (int i = 0; i < BIG; i++) {
        lock_lock(lock);
        counter += 1;
        lock_unlock(lock);
    }

    printf("counter: %d\n", counter);
}