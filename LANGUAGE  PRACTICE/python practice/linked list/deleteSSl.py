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
        for i in range (pos-1):
            temp=temp.next
        np.next=temp.next
        temp.next=np
    def delete_at_beginning(self):
        temp=self.head
        self.head=temp.next
        temp=None
    def delete_at_end(self):
        temp=self.head.next
        prev=self.head
        while temp.next:
            prev=prev.next
            temp=temp.next
        prev.next=None
        temp=None
    def delete_at_position(self,pos):
        temp=self.head.next
        prev=self.head
        for i in range(1,pos-1):
            prev=prev.next
            temp=temp.next
        prev.next=temp.next
        temp.next=None
        temp=None
            
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

l.insert_at_begeinning(0)

l.insert_at_end(4)

l.insert_at_position(2.5,2)
l.display()
l.delete_at_beginning()
l.display()
l.delete_at_end()
l.display()
l.delete_at_position(2)
l.display()