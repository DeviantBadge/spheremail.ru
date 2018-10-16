def brackets(n):
    yield from gen(n, 0, 0, '')


def gen(n, opened, closed, result):
    if opened + closed == 2 * n:
        yield result
    if opened < n:
        yield '\n'.join(gen(n, opened + 1, closed, result + '('))
    if opened > closed:
        yield '\n'.join(gen(n, opened, closed + 1, result + ')'))


if __name__ == "__main__":
    print(''.join(brackets(int(input()))))
