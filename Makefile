CFLAGS = -O3 -Wall -Werror -I src/include -pthread 
SRCS_IDLE_SERIAL = src/utils/* src/idle_experiment/serial_main.c
SRCS_IDLE_PARALLEL = src/utils/* src/idle_experiment/parallel_main.c src/locks/*
SRCS_PARALLEL_SCALING = src/utils/* src/idle_experiment/parallel_scaling.c src/locks/*


idle_serial: $(SRCS_IDLE_SERIAL)
	gcc $(CFLAGS) -o idle_serial $(SRCS_IDLE_SERIAL) 

idle_parallel: $(SRCS_IDLE_PARALLEL)
	gcc $(CFLAGS) -o idle_parallel $(SRCS_IDLE_PARALLEL) 

parallel_scaling: $(SRCS_PARALLEL_SCALING)
	gcc $(CFLAGS) -o parallel_scaling $(SRCS_PARALLEL_SCALING) 

all:
	make idle_serial
	make idle_parallel