a=['a',3,55,"notty",90,'h']
def remove(x):
    for i in x[:]:
        if  not isinstance(i,str):
            x.remove(i)
remove(a)
print(a)           
