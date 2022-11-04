#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BIG 2000000000
#define TAS_LOCK_TYPE 0
#define PTHREAD_LOCK_TYPE 1  // Note: we're just wrapping this
#define A_LOCK_TYPE 2
#define TTAS_LOCK_TYPE 3

typedef struct {
    volatile int state;  // 0 is false, 1 is true
} tas_lock_t;

typedef struct {
    volatile int* flags_array;
    volatile int tail;
} a_lock_t;

typedef struct {
    pthread_mutex_t* mutex;
} pthread_lock_t;

typedef struct {
    volatile int state;  // 0 is false, 1 is true
} ttas_lock_t;

typedef union {
    tas_lock_t* tas_lock;
    a_lock_t* a_lock;
    pthread_lock_t* pthread_lock;
    ttas_lock_t* ttas_lock;
} __lock_t;

typedef struct {  // our wrapper class
    int locktype;
    __lock_t* lock;
} lock_t;

#endif