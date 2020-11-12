from math import  sqrt 
a = float(input("a = "))
b = float(input("b = "))
c = float(input("c = "))

if (a == 0 and b == 0):
        if (c == 0):
            print("Все корни верны")
        else:
            print ("Нет корней")
elif (a == 0):
        if (c == 0):
            print ("Корнем уравнения являеться 0")
        else:
            f = -1 * (c / b)
            print ("Корень равен ",f)
elif (b == 0):
        if (c == 0):
            print ("Корень уравнения 0")
        elif ((-1 * (c / a)) > 0):
            x = sqrt((-1 * (c / a)))
            print ("Первый корень равен, x,\n ")
            x = -1 * sqrt((-1 * (c / a)))
            print ("Второй корень равен, x ")
        else:
            print ("Корни невещественные")
elif (c == 0):
        print ("Первый корень равен 0")
        x = b / a;
        print ("Второй корень равен ")
else:
         if ((b * b - 4 * a * c) > 0):
            x = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a)
            print ("Первый корень равен ",x)
            x = (-1 * b - sqrt(b * b - 4 * a * c)) / (2 * a)
            print ("Второй корень равен ")
         elif ((b * b - 4 * a * c) < 0):
          print ("Корни невещественные")
         else:
            x = (-1 * b + sqrt(b * b - 4 * a * c)) / (2 * a)
            print (x)
