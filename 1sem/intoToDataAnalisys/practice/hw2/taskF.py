def binomial(n):
    for i in range(-1, n):
        res = res * (n - i) // (i + 1) if i >= 0 else 1
        yield str(res)


if __name__ == "__main__":
    for i in map(int, input().split()):
        print(' '.join(binomial(i)))
