
import subprocess

import constants


def lock_fairness_experiment():
    # Ns = [1, 2, 4, 8, 14] 14 doesn't work on my Macbook
    Ns = [1, 2, 4, 8]

    for lock_type in constants.LOCKTYPES:
        print(f"for locktype={lock_type}")

        for n in Ns:
            mean_max_accesses = 0
            mean_min_accesses = 0
            for _ in range(constants.RERUN_COUNT):
                # print('     .')

                rv = subprocess.run(
                    [
                        constants.LOCK_FAIRNESS,
                        lock_type,
                        str(n)
                    ],
                    capture_output=True,
                    text=True,
                )
                # parallel_time = float(rv_parallel.stdout.split(":")[-1].strip())
                max_accesses = float(rv.stdout.split("max_accesses:")[-1].strip().split("\n")[0])
                min_accesses = float(rv.stdout.split("min_accesses:")[-1].strip().split("\n")[0])

                mean_max_accesses += max_accesses
                mean_min_accesses += min_accesses

            print(f"  n={n}: ratio max to min accesses: {mean_max_accesses / mean_min_accesses}")

    print("\n")


lock_fairness_experiment()
