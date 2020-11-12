from math import pow
print ("Введите число")
n = int(input())
a = 1
x = 0
c = 0
b = 0
while a <= n:
    c = pow(2,x)
    if x <= n and c <= n:
          b = b+1
    else:
        n = x
    x = x + 1
    a = a + 1
print(b)
