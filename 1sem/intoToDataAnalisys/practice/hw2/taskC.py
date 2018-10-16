import re
from functools import reduce
from operator import setitem


def solution(x):
    pass


def solution1(x):
    return list(map(lambda string: int(''.join(re.compile("\\d+").findall(string))[::-1]), x))


def solution2(x):
    return list(map(lambda p: p[0] * p[1], x))


def solution3(x):
    return list(filter(lambda p: p % 6 in {0, 2, 5}, x))


def solution4(x):
    return list(filter(lambda p: p, x))


# сказано map - сделано
def solution5(x):
    return list(map(lambda room: (setitem(room, 'square', room['width'] * room['length']), room)[1], x))


def solution6(x):
    return list(map(lambda room: (setitem(room, 'square', room['width'] * room['length']), room)[1], x.copy()))


def solution7(x):
    return list(map(lambda room: (setitem(room, 'square', room['width'] * room['length']), room.copy(), room.pop('square', None))[1], x.copy()))


def solution8(x):
    return reduce(lambda res, elem: (res[0] + elem['height'], res[1] + 1), x, (0, 0))


def solution9(x):
    return list(map(lambda student: student['name'], filter(lambda student: student['gpa'] > 4.5, x)))


def solution10(x):
    return list(filter(lambda ticket: sum(map(int, ticket[0::2])) == sum(map(int, ticket[1::2])), x))


if __name__ == '__main__':
    rooms = [
        {"name": "комната1", "width": 2, "length": 4},
        {"name": "комната2", "width": 2.5, "length": 5.6},
        {"name": "кухня", "width": 3.5, "length": 4},
        {"name": "туалет", "width": 1.5, "length": 1.5},
    ]
    print(solution7(rooms))
    print(rooms)

    students = [
        {'name': 'Alina', 'gpa': 4.57},
        {'name': 'Sergey', 'gpa': 5.0},
        {'name': 'Nastya', 'gpa': 4.21},
        {'name': 'Valya', 'gpa': 4.72},
        {'name': 'Anton', 'gpa': 4.32},
    ]
    print(solution9(students))
    print(solution10(['165033', '477329', '631811', '478117', '475145', '238018', '917764', '394286']))

solutions = {
    'solution1': solution1,
    'solution2': solution2,
    'solution3': solution3,
    'solution4': solution4,
    'solution5': solution5,
    'solution6': solution6,
    'solution7': solution7,
    'solution8': solution8,
    'solution9': solution9,
    'solution10': solution10,
}
