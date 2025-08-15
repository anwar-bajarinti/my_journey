class CDNode:
    def __init__(self, data):
        self.data = data
        self.prev = self
        self.next = self

class CircularDoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def insert(self, data):
        new_node = CDNode(data)
        if not self.head:
            self.head = self.tail = new_node
        else:
            new_node.prev = self.tail
            new_node.next = self.head
            self.tail.next = new_node
            self.head.prev = new_node
            self.tail = new_node

    def display(self):
        if not self.head:
            print("Empty list")
            return
        cur = self.head
        while True:
            print(cur.data, end=" <-> ")
            cur = cur.next
            if cur == self.head:
                break
        print("(back to head)")

# Test
print("Circular Doubly Linked List:")
cdll = CircularDoublyLinkedList()
cdll.insert(100)
cdll.insert(200)
cdll.insert(300)
cdll.display()  # Output: 100 <-> 200 <-> 300 <-> (back to head)
print()
