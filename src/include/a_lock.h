#include "types.h"

bool a_lock_init(a_lock_t* tas_lock);

bool a_lock_lock(a_lock_t* tas_lock);

bool a_lock_unlock(a_lock_t* tas_lock);

bool a_lock_destroy(a_lock_t* tas_lock);