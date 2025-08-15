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
            print("None")
    def insert_at_beginning(self,data):
        new_node=Node(data)
        new_node.next=self.head
        self.head.prev=new_node
        self.head=new_node
    def insert_at_end(self,data):
        new_node=Node(data)
        if self.head is None:
            self.head=new_node
        else:
            temp=self.head.next
            prev=self.head
            while temp is not None:
                temp=temp.next
                prev=prev.next
            new_node=Node(data)
            prev.next=new_node
            new_node.prev=prev
    def insert_at_position(self,data,pos):
        new_node=Node(data)
        temp=self.head.next
        prev=self.head
        for i in range(pos-1):
            temp=temp.next
            prev=prev.next
        new_node.next=temp
        temp.prev=new_node
        prev.next=new_node
        new_node.prev=prev
    def delete_at_beginning(self):
        temp=self.head
        self.head=self.head.next
        self.head.prev=None
        temp=None
    def delete_at_end(self):
        temp=self.head.next
        prev=self.head  
        while temp.next is not None:
            temp=temp.next
            prev=prev.next
        prev.next=None
        temp=None
    def delete_at_position(self,pos):
        temp=self.head.next
        prev=self.head
        for i in range(pos-1):
            temp=temp.next
            prev=prev.next
        prev.next=temp.next
        temp.prev=prev
        temp=None
        
                
l=Dll()

n1=Node(10)
l.head=n1
n2=Node(20)
n1.next=n2
n2.prev=n1
l.display()
l.insert_at_beginning(100)
l.display()
l.insert_at_end(200)
l.display()
l.insert_at_position(150,2)
l.display()
l.delete_at_beginning()
l.display()
l.delete_at_end()   
l.display()
l.insert_at_beginning(29)
l.insert_at_beginning(39)
l.insert_at_beginning(49)
l.display()
l.delete_at_position(2)
l.display()