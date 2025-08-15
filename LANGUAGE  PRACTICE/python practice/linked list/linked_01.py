class Node:
    def __init__(self,data):
        self.data=data
        self.next=None
class LinkedList:
    def __init__(self):
        self.head=None
    def display(self):
        if self.head is None:
            return print("List is empty")
        else:
            temp=self.head
            while temp:
                print(temp.data,"-->",end=' ')
                temp=temp.next
l=LinkedList()
n=Node(1)
l.head=n
n1=Node(2)
n.next=n1
n2=Node(3)
n1.next=n2
l.display()