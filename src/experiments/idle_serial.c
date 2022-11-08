#include "serial_main.h"

int main() {
    StopWatch_t* stopwatch = malloc(sizeof(StopWatch_t));
    startTimer(stopwatch);

    volatile int counter = 0;
    for (int i = 0; i < BIG; i++) {
        counter += 1;
    }
    counter;  // so we don't get unused variable warning

    stopTimer(stopwatch);
    double elapsed_time = getElapsedTime(stopwatch);
    printf("elapsed_time: %f\n", elapsed_time);
    free(stopwatch);
}