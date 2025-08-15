def select(a):
    n=len(a)
    for i in range(n-1):
        min=i
        for j in range(i+1,n):
            if a[j]<a[min]:
                min=j
       
        a[i],a[min]=a[min],a[i]
        
    return a
b=[3,8,0,3,7,55,33,98,6,2]
c=select(b)
print(c)
print(f'smallest{c[0]}')
print(f'greatest{c[-1]}')
