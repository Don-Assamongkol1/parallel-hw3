#include "a_lock.h"

#define STEP_SIZE 16  // how large one step inside this array should be, since we padded

bool a_lock_init(a_lock_t* a_lock) {
    a_lock->flags_array = malloc(sizeof(volatile int) * STEP_SIZE * a_lock->size);  // 16 is for the padding
    a_lock->thread_id_to_slot = malloc(sizeof(int) * a_lock->size);
    a_lock->tail = 0;

    // set the first flag to true
    a_lock->flags_array[0] = 1;

    // set all other flags to zero
    for (int i = 1; i < a_lock->size; i++) {
        a_lock->flags_array[STEP_SIZE * i] = 0;
    }

    return true;
}

bool a_lock_lock(a_lock_t* a_lock, int threadID) {
    int slot = __sync_fetch_and_add(&(a_lock->tail), STEP_SIZE) % a_lock->size;  // add by STEP_SIZE=16 b/c we have padding
    a_lock->thread_id_to_slot[threadID] = slot;                                  // have the lock remember this thread (id)'s position in the queue

    while (!a_lock->flags_array[slot]) {
        ;
    }

    return true;
}

bool a_lock_unlock(a_lock_t* a_lock, int threadID) {
    int slot = a_lock->thread_id_to_slot[threadID];              // here, get the slot that this thread was queued up to
    a_lock->flags_array[slot] = 0;                               // our thread is done, indicate so in the flags array
    a_lock->flags_array[(slot + STEP_SIZE) % a_lock->size] = 1;  // allow the other thread to go
    return true;
}

bool a_lock_destroy(a_lock_t* a_lock) {
    return true;
}