import numpy as np
import pandas as pd


def peak_finder(s):
    res = np.array([])
    for i in range(1, s.size - 1):
        if s[i-1] < s[i] and s[i+1] < s[i]:
            res = np.append(res, [i])
    return res
