r = 37
a = [0] * r
i = 0
t = 0
q = 0
w = 0
p = 0
red = [1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36]
for i in range (37):
    a[i] = 0
while 1:
    u = 0
    o = 0
    l = 0
    x = int(input())
    if x < 0:
        break
    else:
        a[x]=a[x] + 1
        for t in range (18):
            if x == red[t]:
                q=q+1
                break
            elif t == 17:
                w=w+1
                break
    for u in range (37):
        if a[u] > p:
            p = a[u]
    for o in range (37):
        if a[o] == p:
            print (o)
    for l in range (37):
        if a[l] == 0:
            print (l)
    print("Красные: ",q," Черные: ",w)
