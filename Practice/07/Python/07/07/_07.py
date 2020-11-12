from math import  sqrt 
f = int(input("Введите 1 для подсчета площади с помощью длин сторон или 2 для метода координат: "))            

if (f == 1):
    a = int(input("Введите первую сотрону: "))
    b = int(input("Введите вторую сотрону: "))
    c = int(input("Введите третью сотрону: "))
    if ((a < b + c) and (b < a + c) and (c < a + b)):
        p = (a + b + c) / 2
        S = sqrt(p * (p - a) * (p - b) * (p - c))
        print("S = ", S)
    else:
        print("Несуществующий треугольник")
elif (f == 2):
    x1 = int(input("Введите координату x1: "))
    y1 = int(input("Введите координату y1: "))
    x2 = int(input("Введите координату x2: "))
    y2 = int(input("Введите координату y2: "))
    x3 = int(input("Введите координату x3: "))
    y3 = int(input("Введите координату y3: "))
    a = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)))
    b = sqrt(((x3 - x2) * (x3 - x2)) + ((y3 - y2) * (y3 - y2)))
    c = sqrt(((x3 - x1) * (x3 - x1)) + ((y3 - y1) * (y3 - y1)))
    if ((a < b + c) & (b < a + c) & (c < a + b)):
        p = (a + b + c) / 2
        S = sqrt(p * (p - a) * (p - b) * (p - c))
        print("S = ", S)
    else:
        print("Несуществующий треугольник")
else:
     print("Некорректный ввод")
