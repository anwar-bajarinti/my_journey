from array import array
a = array('i', [1, 99,55,11,75,25,33,89,1,23])
def sort(x):
    for i in range(len(x)-1):
        for j in range(len(x)-i-1):
            if x[j]>x[j+1]:
                x[j],x[j+1]=x[j+1],x[j]
sort(a)
print(a)
