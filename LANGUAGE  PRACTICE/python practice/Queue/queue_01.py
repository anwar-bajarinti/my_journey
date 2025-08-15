class Queue(object):
    def __init__(self):
        self.queue=[]

    def enqueue(self,data):
        self.queue.append(data)
        return f'{data } added to the queue'
    def dequeue(self):
        return f'{self.queue.pop()} removed from the queue'
    def isempty(self):
        return self.queue==[]
    def size(self):
        return len(self.queue)
if __name__=="__main__":
    a=Queue()
    print(a.enqueue(10))
    print(a.enqueue(20))
    print(a.enqueue(30))
    print(a.dequeue())
    print(a.isempty())
    print(a.dequeue())
    print(a.dequeue())
    print(a.isempty())
