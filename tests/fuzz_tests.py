from collections import namedtuple
import xarray
from lowtran.base import golowtran
import numpy as np
import random
import pandas as pd
import time
import matplotlib.pyplot as plt
from tqdm import tqdm


def slanted_trans(wlshort, wllong, wlstep, model, h1, h2, range_km) -> xarray.Dataset:

    c1 = {
        # "model": 1,  # 0: user meterological data
        "itype": 2,  # 1: horizontal path
        "iemsct": 0,  # 0: transmittance model
        "len": 0,
        # 1: for user-defined atmosphere on horizontal path (see Lowtran manual p.42)
        "im": 1,
        "ird1": 1,  # 1: use card 2C2,
        "h1": h1,
        "h2": h2,
        "range_km": range_km,
        "wlshort": wlshort,
        "wllong": wllong,
        "wlstep": wlstep,
        "model": model
    }

    start = time.perf_counter_ns()
    res = golowtran(c1)
    return [time.perf_counter_ns() - start, res]


def rand_range(min, max, integer=False):
    if not integer:
        return random.random()*(max-min) + min
    else:
        return random.randint(min, max)


def main():

    random.seed(24112021)

    FuzzConfig = namedtuple("FuzzConfig", ["wlshort_range",
                                           "wllong_range",
                                           "model_range",
                                           "range_km_range",
                                           "h1_range",
                                           "h2_range",
                                           "wlstep_range",
                                           "random_items"])

    fuzz_config = FuzzConfig(wlshort_range=(200, 10_000),
                             wllong_range=(200, 10_000),
                             model_range=(1, 5),
                             range_km_range=(1, 100),
                             h1_range=(5, 50),
                             h2_range=(5, 50),
                             wlstep_range=(5, 5),
                             random_items=1000)

    times = []
    for item_i in tqdm(range(fuzz_config.random_items)):

        wlshort = rand_range(*fuzz_config.wlshort_range)
        # ensure wllong > wlshort
        wllong = rand_range(wlshort, fuzz_config.wllong_range[1])

        model = rand_range(*fuzz_config.model_range, integer=True)
        h1 = rand_range(*fuzz_config.h1_range)
        h2 = rand_range(*fuzz_config.h2_range)

        # must be at min the distance between h2 - h1 if vertical, add 1 to stop vertical
        range_km = rand_range(h2-h1 + 1, fuzz_config.range_km_range[1])

        wlstep = rand_range(*fuzz_config.wlstep_range, integer=True)

        time_taken, TR = slanted_trans(
            wlshort, wllong, wlstep, model, h1, h2, range_km)

        df = TR.to_dataframe()

        times.append(time_taken)

        # print(time_taken)

    # plt.hist(times, bins=1000, log=True)
    print(np.average(times) / 1e6, "milliseconds")
    # plt.show()
    # drop time as object for some reason

    # df.drop('time', axis=1, inplace=True)

    # df.to_hdf('./generated/fuzz_test.h5', key="df")
    # store = pd.HDFStore("./generated/fuzz_test.h5")

    # for k, v in fuzz_config._asdict().items():
    #     store.get_storer("df").attrs[k] = v
    # store.put("df", df)

    # store.close()


if __name__ == "__main__":
    main()
