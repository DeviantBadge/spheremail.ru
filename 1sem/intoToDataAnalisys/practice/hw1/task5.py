import numpy as np
import pandas as pd


def df_diag_ones(s):
    res = s.copy()
    for i in range(s.shape[0]):
        for j in range(s.shape[1]):
            if i == j or i == s.shape[0] - j - 1:
                res[i][j] = 1
    return res