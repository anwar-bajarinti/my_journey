class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class CircularLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def display(self):
        if self.head is None:
            print("List is empty")
            return
        temp = self.head
        while True:  # Corrected condition
            print(temp.data, "-->", end=" ")
            temp = temp.next
            if temp == self.head:
                break
        print("None")

    def insert_at_beginning(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
            new_node.next = self.head  # Circular linkage
        else:
            new_node.next = self.head
            self.head = new_node
            self.tail.next = self.head  # Maintain circular linkage

    def insert_at_end(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
            new_node.next = self.head  # Circular linkage
        else:
            self.tail.next = new_node
            self.tail = new_node
            self.tail.next = self.head  # Maintain circular linkage
    def delete_at_beginning(self):
        if self.head is None:
            print("List is empty")
            return
        if self.head == self.tail:
            self.head = None
            self.tail = None
            return
        temp=self.head
        self.head = temp.next
        self.tail.next = self.head
        temp=None
    def delete_at_end(self):
        if self.head is None:
            print("List is empty")
            return
        if self.head == self.tail:
            self.head = None
            self.tail = None
            return
        temp=self.head
        while temp.next!=self.tail:
            temp=temp.next
        temp.next=self.head
        self.tail=temp
        temp=None
    def delete_at_position(self,position):
        if self.head is None:
            print("List is empty")
            return
        if position==0:
            self.delete_at_beginning()
            return
        temp=self.head
        temp1=self.head.next
        for i in range(position-1):
            temp=temp.next
            temp1=temp1.next
    
        temp.next=temp1.next
        temp1=None

# Corrected initialization
l = CircularLinkedList()
l.insert_at_end(10)  # Use insert_at_end() instead of manual assignment
l.display()
l.insert_at_end(20)
l.insert_at_beginning(5)
l.insert_at_end(30)
l.insert_at_beginning(1)
l.display()
 
l.delete_at_beginning()
l.display()
l.delete_at_end()
l.display()
l.insert_at_beginning(1)
l.insert_at_end(30)
l.inseert_at_end(40)
l.insert_at_beginning(0)
l.delete_at_position(1)
l.display()
