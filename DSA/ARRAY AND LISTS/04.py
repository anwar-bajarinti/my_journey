a=[]
b=int(input("enter no upto u want"))
def prime(x,n):
    for i in range(n):
        if i%2 !=0:
         x.append(i)
prime(a,b)
print(a)