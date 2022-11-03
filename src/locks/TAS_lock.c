#include "TAS_lock.h"

bool tas_lock_init(tas_lock_t* tas_lock) {
    tas_lock->state = false;
    return true;
}

bool tas_lock_lock(tas_lock_t* tas_lock) {
    return true;
}

bool tas_lock_unlock(tas_lock_t* tas_lock) {
    return true;
}

bool tas_lock_destroy(tas_lock_t* tas_lock) {
    return true;
}