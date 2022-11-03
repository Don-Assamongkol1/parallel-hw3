#include "TAS_lock.h"
#include "TTAS_lock.h"
#include "a_lock.h"
#include "pthread_lock.h"
#include "types.h"

void lock_init(lock_t* lock);

void lock_lock(lock_t* lock);

void lock_unlock(lock_t* lock);

void lock_destroy(lock_t* lock);