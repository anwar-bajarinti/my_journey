a=[4,7,8,0,2,44,55]
def cal(x):
    count=0
    for i in range(len(x)):
        count+=x[i]
    return count/len(a)
print(cal(a))