import subprocess
import os
import filecmp
import glob

import constants


def idle_overhead_experiment():
    mean_serial_time = 0
    for _ in range(constants.RERUN_COUNT):
        print('.')

        rv_serial = subprocess.run([constants.IDLE_SERIAL], capture_output=True, text=True)
        serial_time = float(rv_serial.stdout.split(":")[-1].strip())
        mean_serial_time += serial_time

    print(f"mean_serial_time: {mean_serial_time / constants.RERUN_COUNT}")

    # for lock_type in constants.LOCKTYPES:
    #     for _ in range(constants.RERUN_COUNT):

    #         rv_serial = subprocess.run(
    #             [
    #                 constants.SERIAL_EXECUTABLE,
    #                 str(n),
    #                 str(T),
    #                 str(W),
    #                 str(trial_num),
    #                 constants.UNIFORM,
    #             ],
    #             capture_output=True,
    #             text=True,
    #         )
    #         serial_time = float(rv_serial.stdout.split(":")[-1].strip())
    #         mean_serial_time += serial_time

    #         rv_serial_queue = subprocess.run(
    #             [
    #                 constants.SERIAL_QUEUE_EXECUTABLE,
    #                 str(n),
    #                 str(T),
    #                 str(W),
    #                 str(trial_num),
    #                 constants.UNIFORM,
    #             ],
    #             capture_output=True,
    #             text=True,
    #         )
    #         serial_queue_time = float(rv_serial_queue.stdout.split(":")[-1].strip())
    #         mean_serial_queue_time += serial_queue_time

    #         trial_num += 1


idle_overhead_experiment()
