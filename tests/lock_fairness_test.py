
import subprocess

import constants

import re
# >>> string1 = "498results should get"
# >>> int(re.search(r'\d+', string1).group())
# 498


def lock_fairness_experiment():
    print("lock fairness test")
    Ns = [1, 2, 4, 8, 14] # 14 doesn't work on my Macbook
    # Ns = [1, 2, 4, 8]

    for lock_type in constants.LOCKTYPES:
        print(f"for locktype={lock_type}")

        for n in Ns:

            # for _ in range(constants.RERUN_COUNT):
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
            print([
                constants.LOCK_FAIRNESS,
                lock_type,
                str(n)
            ])
            array = rv.stdout.split("\n")[:-1]
            array = [int(num) for num in array]
            max_accesses = max(array)
            array = [num / max_accesses for num in array] # this way we scale the accesses as a percentage of the max number of accesses that one thread got


            print('n: ', n)
            print(list(sorted(array)))

    print("\n")


lock_fairness_experiment()
