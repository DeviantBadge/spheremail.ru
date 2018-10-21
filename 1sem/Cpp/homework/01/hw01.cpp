#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <stdexcept>
#include "numbers.dat"

using namespace std;

inline int toInteger(const char *s) {
    char *p;
    int value = strtol(s, &p, 10);
    if (*p != 0) {
        string error_message("Input string - \"");
        error_message += s;
        error_message += "\" is not a number.";
        throw invalid_argument(error_message);
    }
    return value;
}

void print_vec(vector<int> vec) {
    for (auto &num: vec) {
        cout << num << "\n";
    }
//    cout << endl;
}

int bin_search(const int *vec, int value, int left_border, int right_border) {
    int middle;
    while (right_border > left_border) {
        middle = (left_border + right_border) / 2;
        if (value <= vec[middle])
            right_border = middle;
        else
            left_border = middle + 1;
    }
    return vec[left_border] == value ? left_border : -1;
}

vector<bool> computePrimeMap(int amount) {
    vector<bool> primes(amount, true);
    primes[0] = primes[1] = false;
    for (int i = 2; i * i < amount; i++) {
        if (primes[i])
            for (int j = i * i; j < amount; j += i)
                primes[j] = false;
    }
    return primes;
}

pair<int, int> getInputPair(int argc, char *argv[], int number) {
    if ((number + 1) * 2 + 1 > argc)
        throw invalid_argument("Too big pair number.");
    return pair<int, int>(toInteger(argv[number * 2 + 1]), toInteger(argv[number * 2 + 2]));
}

int main(int argc, char *argv[]) {
    if (((argc - 1) % 2 == 1) || (argc == 1))
        return -1;

    vector<bool> primes = computePrimeMap(Data[Size - 1] + 1);
    int inputPairAmount = argc / 2;
    vector<int> result(inputPairAmount, 0);
    pair<int, int> currentPair;
    int startIndex;
    int endIndex;

    int endValue;
    int curResult;

    for (int i = 0; i < inputPairAmount; i++) {
        try {
            currentPair = getInputPair(argc, argv, i);
        } catch (invalid_argument e) {
            return -1;
        }
        if (currentPair.first > currentPair.second)
            continue;

        startIndex = bin_search(Data, currentPair.first, 0, Size - 1);
        if (startIndex == -1)
            continue;
        endIndex = bin_search(Data, currentPair.second, 0, Size - 1);
        if (endIndex == -1)
            continue;
//        cout << startIndex << " " << endIndex << endl;
//        cout << currentPair.first << " " << currentPair.second << endl;

        curResult = 0;
        endValue = Data[endIndex];
        // понимаю что читаю 2 раза вместо одного, но по моему скромному мнению так намного легче воспринимается код
        for (int j = startIndex; Data[j] <= endValue; j ++){
            if (primes[Data[j]])
                curResult ++;
        }
        result[i] = curResult;
    }

    print_vec(result);
    return 0;
}