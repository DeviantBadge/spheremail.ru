def solution1(x):
    return [letter * 4 for letter in x]


def solution2(x):
    return [(number + 1) * letter for number, letter in enumerate(x)]


def solution3(x):
    return list(filter(lambda num: (num % 3 == 0) | (num % 5 == 0), x))


# этот вариант многомерный и ему все равно какая вложенность
# вариант [[1, [2, 3]], [4, 5, 6, 7], [8, 9], [0]] раскладывается на ура
def solution4a(x):
    result = []
    __solution4a(x, result)
    return result


def __solution4a(x, buff):
    try:
        for i in x:
            __solution4a(i, buff)
        return
    except TypeError:
        pass
    buff.append(x)


def solution4(x):
    return [j for i in x for j in i]


def solution5(x):
    return [(i, j, k) for i in range(1, x + 1) for j in range(i, x + 1) for k in range(j, x + 1) if
            (i ** 2 + j ** 2 == k ** 2)]


def solution6(x):
    return [[j + i for i in x[1]] for j in x[0]]


# todo ask teacher about it
def solution7(x):  # wanted to write for j in range(len(x[i])), but dont know how to do it
    return [[x[i][j] for i in range(len(x))] for j in range(len(x[0]))]


def solution8(x):
    return [list(map(int, subList.split(' '))) for subList in x]


def solution9(x):
    return dict([(chr(ord('a') + num), num ** 2) for num in x])


def solution10(x):
    return set(map(lambda name: name.title(), [word for word in x if len(word) > 3]))


if __name__ == '__main__':
    print(solution1('python'))
    print(solution2('python'))
    print(solution3(range(16)))
    print(solution4([[1, 2, 3], [4, 5, 6, 7], [8, 9], [0]]))
    print(solution5(15))
    print(solution6(([0, 1, 2], [0, 1, 2, 3, 4])))
    print(solution7([[1, 2], [3, 4], [5, 6]]))
    print(solution8(["0", "1 2 3", "4 5 6 7", "8 9"]))
    print(solution9(range(0, 7)))
    print(solution10(['Alice', 'vova', 'ANTON', 'Bob', 'kAMILA', 'CJ', 'ALICE', 'Nastya']))

solutions = {
    'solution1': solution1,
    'solution2': 0,
    'solution3': 0,
    'solution4': 0,
    'solution5': 0,
    'solution6': 0,
    'solution7': 0,
    'solution8': 0,
    'solution9': 0,
    'solution10': 0,
}
