k = type(True)
f = 0
j = 0
b = 'Ответ:'
print("Введите количество банкнот ENTER!")
n = int(input())
print("Введите банкноты через ENTER!")
while j < n:
    
    a = str(input())
    if a[0] == 'a' and a[4] == '5' and a[5] == '5' and a[6] == '6' and a[7] == '6' and a[8] == '1':
        b = b + ' ' + a
    else:
        f = f + 1
    j = j + 1
if f == n:
    print("-1")
else:
    print(b)
