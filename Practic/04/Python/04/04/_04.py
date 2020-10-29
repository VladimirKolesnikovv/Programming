print("Посчиать с дополнительной переменной-1,2-без")
d = int(input())
if d == 1:
    print('Введите 1 число')
    a = int(input())
    print("Введите 2 число")
    b = int(input())
    c = a  
    a = b  
    b = c
    print("Значение первого числа", a)
    print("Значение второго числа", b)
elif d == 2:
    print('Введите первого  число')
    a = int(input())
    print("Введите второго число")
    b = int(input())
    a,b=b,a
    print("Значение первого  числа", a)
    print("Значение второго  числа", b)
else:
    print("Ошибка ввода")
