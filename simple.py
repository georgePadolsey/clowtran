import clowtran
import matplotlib.pyplot as plt

import lowtran.base


def main():

    for model_i in range(1, 6):
        res = clowtran.run(1, 2)

        plt.plot(res[:, 0]*1e3, res[:, 1])

    plt.show()


if __name__ == "__main__":
    main()
