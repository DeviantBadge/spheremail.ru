import numpy as np


def zeros_insert(k, n):
    l = 1
    for i in range(k.shape[0] - 1):
        for j in range(n):
            k = np.insert(k, l, 0)
            l += 1
        l += 1
    return k