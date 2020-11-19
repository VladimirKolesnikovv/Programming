import json
from array import *
c=0
p=0
m=list('')
x='a'
with open('in.json','r') as f:
    a=f.read()
    data=json.loads(a)
    h=dict(data[0])
    k=h['userId']
    for l in range(len(data)):
        h=dict(data[l])
        if (k==h['userId']):
            if (h['completed']==1):
                c+=1
        else:
            d={'userId':k,
                'task_completed':c
            }
            m.append(x)
            m[p]=d
            p+=1
            c=0
            k=h['userId']
            if (h['completed']==1):
                c+=1
    d={'userId':k,
        'task_completed':c
    }
    m.append(x)
    m[p]=d            
print(m)
with open ('out.json','w') as b:
    b=json.dump(m,b,indent=3)
  
    
        
    
