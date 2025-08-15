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

# Corrected initialization
l = CircularLinkedList()
l.insert_at_end(10)  # Use insert_at_end() instead of manual assignment
l.display()
l.insert_at_end(20)
l.insert_at_beginning(5)
l.insert_at_end(30)
l.insert_at_beginning(1)
l.display()
 

