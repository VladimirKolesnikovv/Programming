print("Введите число для его проверки")
a = int(input())
b = 1
v = 2
i = 2
while i < a:
    if (a % v) == 0:
        print ("Составное число")
        b = v
        a = v
    v = v + 1
    i = i + 1
if b == 1:
    print ("Простое число")
