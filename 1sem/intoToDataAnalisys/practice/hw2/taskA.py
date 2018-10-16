def ackermann(m, n):
    ackermann.counter = 0
    return ack(m,n)


def ack(m, n):
    ackermann.counter += 1
    if m == 0:
        return n + 1
    else:
        if n == 0:
            return ack(m - 1, 1)
        else:
            return ack(m-1, ack(m, n-1))


if __name__ == '__main__':
    print(ackermann(3, 5), ackermann.counter)
    print(ackermann(3, 5), ackermann.counter)
