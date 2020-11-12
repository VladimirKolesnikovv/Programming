import random
a = 1
c = 5
o = 0
i = 1
print("Приветсвую игрок,попробую угадать число!")
while i <= c:
    if a == 1 or a == 0:
        b = random.randint(0,100)
        print("Введите число")
    if a == 5:
        h = int(input())
        if h == b:
            print("Поздравляю!Вы угадали")
            print("Хотите начать сначала?(1-Да)")
            f = int(input())
            if f == 1:
                c = c * 2
                a = 0
        else:
            print ("Вы проиграли. Было загадано:",b)
            print ("Хотите начать сначала?(1-Да)")
            f = int(input())
            if f == 1:
                c = c * 2
                a = 0
    else:
        h = int(input())
        o = o + 1
        if h == b:
            print("Поздравляю!Вы угадали")
            print("Хотите начать сначала?(1-Да)")
            if f == 1:
                c = o + 5
                a = 0
        else:
            if h > b:
                print("Число меньше")
            else:
                print("Число больше")
    a = a + 1
    i = i + 1
