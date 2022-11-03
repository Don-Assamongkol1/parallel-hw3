#include "types.h"

bool pthread_lock_init(pthread_lock_t* tas_lock);

bool pthread_lock_lock(pthread_lock_t* tas_lock);

bool pthread_lock_unlock(pthread_lock_t* tas_lock);

bool pthread_lock_destroy(pthread_lock_t* tas_lock);