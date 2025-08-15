class CSNode:
    def __init__(self, data):
        self.data = data
        self.next = None

class CircularSinglyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def insert(self, data):
        new_node = CSNode(data)
        if not self.head:
            self.head = self.tail = new_node
            self.tail.next = self.head
        else:
            self.tail.next = new_node
            self.tail = new_node
            self.tail.next = self.head

    def display(self):
        if not self.head:
            print("Empty list")
            return
        cur = self.head
        while True:
            print(cur.data, end=" -> ")
            cur = cur.next
            if cur == self.head:
                break
        print("(head again)")

# Test
print("Circular Singly Linked List:")
csll = CircularSinglyLinkedList()
csll.insert(5)
csll.insert(10)
csll.insert(15)
csll.display()  # Output: 5 -> 10 -> 15 -> (head again)
print()
