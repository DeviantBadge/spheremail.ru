y = int(input())
if y % 400 == 0:
    print(1)
else:
    if y % 100 == 0:
        print(0)
    else:
        if y % 4 == 0:
            print(1)
        else:
            print(0)
