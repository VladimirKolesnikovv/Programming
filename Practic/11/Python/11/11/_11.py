print("Введите число и его степень через пробел!")
a,b = input().split(' ')
a = float(a)
b = float(b)
c = float(a)
n = 1
if b == 1:
    print(c)
elif b == 0:
    print(1)
elif b>0:
    while n < b:
        n = n + 1
        a = a * c
    print(a)
else:
    d = float(1/a)
    while n > b:
        n = n - 1
        a = a * d
    print(a)
