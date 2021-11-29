import clowtran
import time
import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt


def main():

    times = []
    for i in tqdm(range(1000)):
        start = time.perf_counter_ns()
        clowtran.run(3,2)
        diff = (time.perf_counter_ns()-start)
        times.append(diff)

    print('{:.2f} +- {:.2f} milliseconds'.format(np.average(times) /
          1e6, np.std(times)/1e6))

    plt.show()


if __name__ == "__main__":
    main()
