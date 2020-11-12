print("Введите число и диапазоны через пробел!")
s, l1, r1, l2, r2 = input().split(' ')
z = 0
s = int (s)
l1 = int (l1)
r1 = int (r1)   
r2 = int (r2)   
l2 = int (l2)   
if s > (r1 + r2) | s < (l1 + l2):
    print (-1, end = '')
else:
    if (s - l1) >= l2:
        if s <= (l1 + r2):
            print (l1, s - l1, end = '')
        else: 
            z = abs (s - (l1 + r2))
            if (l1 + z) < r1 & (r2 - z) > l2:
                print (l1 + z, s - (l1 + z), end = '')
            else: 
                print (-1, end = '')            
    else:
        print (-1, end = '')
