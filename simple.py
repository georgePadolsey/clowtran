import clowtran
import matplotlib.pyplot as plt

import lowtran.base
import numpy as np


def main():

    for model_i in range(1, 6):

        h1 = 5
        h2 = 10
        range_km = 10
        res = clowtran.run(model_i, 2)

        py_res = lowtran.base.golowtran({
            "h1": h1,
            "h2": h2,
            "range_km": range_km,
            "model": model_i,
            "itype": 2,
            "im": 1,
            "iemsct": 0,
            "wlshort": 200,
            "wllong": 5000,
            "wlstep": 5
        })

        # print(py_res["transmission"])

        print(res[:, 0][0:5])
        print([float(x) for x in py_res["wavelength_nm"][0:5]])

        print('mine', res[:, 1][0:5])
        print("py", list([float(x)
              for x in py_res["transmission"].squeeze()[0:5]]))

        print("======")
        print([float(x)
              for x in res[:, 1] - py_res["transmission"].squeeze()][0:5])

        # print(res[-1), 0]
        # print(py_res["wavelength_nm"][-1])
        plt.figure()
        plt.plot(res[:, 0]*1e3, res[:, 1])
        plt.plot(res[:, 0]*1e3, py_res["transmission"].squeeze())
        plt.figure()
        plt.plot(res[:, 0]*1e3, np.abs((res[:, 1] - py_res["transmission"].squeeze()
                                        )))

    plt.show()


if __name__ == "__main__":
    main()
