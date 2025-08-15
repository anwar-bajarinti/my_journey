class Node:
    def __init__(self,data):
        self.data=data
        self.next=None
class LinkedList:
    def __init__(self):
        self.head=None
    def insert_at_begeinning(self,data):
        nb=Node(data)
        nb.next=self.head
        self.head=nb
    def insert_at_end(self,data):
        ne=Node(data)
        temp=self.head
        while temp.next:
            temp=temp.next
        temp.next=ne
    def insert_at_position(self,data,pos):
        np=Node(data)
        temp=self.head
        for i in range (pos-1w):
            temp=temp.next
        np.next=temp.next
        temp.next=np
            
    def display(self):
        if self.head is None:
            return print("List is empty")
        else:
            temp=self.head
            while temp:
                print(temp.data,"-->",end=' ')
                temp=temp.next
        print()
l=LinkedList()
n=Node(1)
l.head=n
n1=Node(2)
n.next=n1
n2=Node(3)
n1.next=n2
l.display()
l.insert_at_begeinning(0)
l.display()
l.insert_at_end(4)
l.display()
l.insert_at_position(2.5,2)
l.display()