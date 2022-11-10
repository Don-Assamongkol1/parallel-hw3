import subprocess
import constants


def idle_overhead_experiment():
    print("idle overhead experiment")
    
    mean_serial_time = 0
    for _ in range(constants.RERUN_COUNT):
        # print('     .')

        rv_serial = subprocess.run([constants.IDLE_SERIAL], capture_output=True, text=True)
        serial_time = float(rv_serial.stdout.split(":")[-1].strip())
        mean_serial_time += serial_time

    print(f"mean_serial_time: {mean_serial_time / constants.RERUN_COUNT}")

    for lock_type in constants.LOCKTYPES:

        mean_parallel_time = 0
        for _ in range(constants.RERUN_COUNT):
            # print('     .')

            rv_parallel = subprocess.run(
                [
                    constants.IDLE_PARALLEL,
                    lock_type,
                ],
                capture_output=True,
                text=True,
            )
            parallel_time = float(rv_parallel.stdout.split(":")[-1].strip())
            mean_parallel_time += parallel_time

        print(f"for locktype {lock_type}")
        print(f"    mean_parallel_time: {mean_parallel_time / constants.RERUN_COUNT}")
        print(f"    mean_serial_time: {mean_serial_time / constants.RERUN_COUNT}")

        print(f"    ratio parallel to serial: {mean_parallel_time / mean_serial_time}")

    print("\n")


idle_overhead_experiment()
