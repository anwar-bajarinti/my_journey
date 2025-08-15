n=int(input(" upto==="))
def fibonac(n):
    a=[0,1]
    sum=1
    j=1
    for i in range(n):
        j=0
        j-=1
        sum=a[i]+a[j]
        a.append(sum)
    return a
b=fibonac(n)
print(b)    