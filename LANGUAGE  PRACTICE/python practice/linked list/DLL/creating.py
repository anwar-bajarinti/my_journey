class Node:
    def __init__(self,data):
        self.data=data
        self.next=None
        self.prev=None
class Dll:
    def __init__(self):
        self.head=None
    def display(self):
        if self.head is None:
            print("List is empty")
        else:
            temp=self.head
            while temp:
                print(temp.data," <-->",end=" ")
                temp=temp.next
l=Dll()

n1=Node(10)
l.head=n1
n2=Node(20)
n1.next=n2
n2.prev=n1
l.display()