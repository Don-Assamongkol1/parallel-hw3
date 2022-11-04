#include "TAS_lock.h"

bool tas_lock_init(tas_lock_t* tas_lock) {
    tas_lock->state = 0;
    return true;
}

bool tas_lock_lock(tas_lock_t* tas_lock) {
    // printf("inside tas_lock_lock\n");
    __sync_fetch_and_or(&(tas_lock->state), 1);
    // while (false) {
    // while (__sync_fetch_and_or(&(tas_lock->state), 1)) {
    //     printf("inside while loop\n");
    //     ;
    // }
    // printf("return of tas_lock_lock\n");
    return true;
}

bool tas_lock_unlock(tas_lock_t* tas_lock) {
    // __sync_fetch_and_and(&(tas_lock->state), 0);
    return true;
}

bool tas_lock_destroy(tas_lock_t* tas_lock) {
    return true;
}