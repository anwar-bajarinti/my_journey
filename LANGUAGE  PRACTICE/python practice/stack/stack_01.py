class stack():
    def __init__(self):
        self.stack=[]
        self.idx=0
    def push(self,data):
        self.stack.insert(self.idx,data)
        self.idx+=1
        return ' {} pushed into the stack'.format(data)
    def pop(self):
        self.idx-=1
        self.stack.pop()
        return ' {} popped from the stack'.format(self.stack.pop())
    def isempty(self):
        return self.stack==[]
if __name__=='__main__':
    a=stack()
    print(a.push(10))
    print(a.push(20))
    print(a.push(30))
    print(a.pop())
    print(a.isempty())
    print(a.pop())
    print(a.pop())
    print(a.isempty())