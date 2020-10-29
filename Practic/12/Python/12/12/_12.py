print ("Введите число")
a = int(input())
i = 1
b = 1
if a < 0:
    print("Введите положительное число")
elif a == 0:
    print ("1")
else:
    while i <= a:
        b = b * i
        i =i + 1
    print(b)
