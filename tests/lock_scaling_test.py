
import subprocess
import os

import constants


def lock_scaling_experiment():
    Ns = [1, 2, 4, 8]
    # Ns = [1, 2, 4, 8, 14]

    mean_serial_time = 0
    for _ in range(constants.RERUN_COUNT):
        rv_serial = subprocess.run([constants.IDLE_SERIAL], capture_output=True, text=True)
        serial_time = float(rv_serial.stdout.split(":")[-1].strip())
        mean_serial_time += serial_time

    print(f"mean_serial_time: {mean_serial_time / constants.RERUN_COUNT}")

    for lock_type in constants.LOCKTYPES:

        print(f"for locktype={lock_type}")
        for n in Ns:
            mean_parallel_time = 0

            for _ in range(constants.RERUN_COUNT):
                rv_parallel = subprocess.run(
                    [
                        constants.LOCK_SCALING,
                        lock_type,
                        str(n)
                    ],
                    capture_output=True,
                    text=True,
                )
                parallel_time = float(rv_parallel.stdout.split(":")[-1].strip())
                mean_parallel_time += parallel_time

            print(f"  n={n}: ratio parallel to serial: {mean_parallel_time / mean_serial_time}")
            # print(f"    mean_parallel_time: {mean_parallel_time / constants.RERUN_COUNT}")
            # print(f"    mean_serial_time: {mean_serial_time / constants.RERUN_COUNT}")


lock_scaling_experiment()


'''
eventually want a graph that's n on the x-axis, and the speedup ratio as a
curve on the y, which will be a curve for each type of lock
'''
