#include "TTAS_lock.h"

bool ttas_lock_init(ttas_lock_t* tas_lock) {
    tas_lock->state = false;
    return true;
}

bool ttas_lock_lock(ttas_lock_t* tas_lock) {
    return true;
}

bool ttas_lock_unlock(ttas_lock_t* tas_lock) {
    return true;
}

bool ttas_lock_destroy(ttas_lock_t* tas_lock) {
    return true;
}