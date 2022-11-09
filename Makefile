CFLAGS = -O3 -Wall -Werror -I src/include -pthread 
SRCS_IDLE_SERIAL = src/utils/* src/experiments/idle_serial.c
SRCS_IDLE_PARALLEL = src/utils/* src/experiments/idle_parallel.c src/locks/*
SRCS_LOCK_SCALING = src/utils/* src/experiments/lock_scaling.c src/locks/*
SRCS_LOCK_FAIRNESS = src/utils/* src/experiments/lock_fairness.c src/locks/*
SRCS_LOCK_EXCLUSIVITY = src/utils/* src/experiments/lock_exclusivity.c src/locks/*


idle_serial: $(SRCS_IDLE_SERIAL)
	gcc $(CFLAGS) -o idle_serial $(SRCS_IDLE_SERIAL) -lm

idle_parallel: $(SRCS_IDLE_PARALLEL)
	gcc $(CFLAGS) -o idle_parallel $(SRCS_IDLE_PARALLEL) -lm

lock_scaling: $(SRCS_LOCK_SCALING)
	gcc $(CFLAGS) -o lock_scaling $(SRCS_LOCK_SCALING) -lm

lock_fairness: $(SRCS_LOCK_FAIRNESS)
	gcc $(CFLAGS) -o lock_fairness $(SRCS_LOCK_FAIRNESS) -lm

lock_exclusivity: $(SRCS_LOCK_EXCLUSIVITY)
	gcc $(CFLAGS) -o lock_exclusivity $(SRCS_LOCK_EXCLUSIVITY) -lm


all: 
	make idle_serial
	make idle_parallel
	make lock_scaling
	make lock_fairness

clean: 
	rm idle_serial
	rm idle_parallel
	rm lock_scaling
	rm lock_fairness