CFLAGS = -O3 -Wall -Werror -I src/include -pthread 
SRCS_IDLE_SERIAL = src/utils/* src/idle_experiment/serial_main.c
SRCS_IDLE_PARALLEL = src/utils/* src/idle_experiment/parallel_main.c src/locks/*


idle_serial: $(SRCS_IDLE_SERIAL)
	gcc $(CFLAGS) -o idle_serial $(SRCS_IDLE_SERIAL) 

idle_parallel: $(SRCS_IDLE_PARALLEL)
	gcc $(CFLAGS) -o idle_parallel $(SRCS_IDLE_PARALLEL) 