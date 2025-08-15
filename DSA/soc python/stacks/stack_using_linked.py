class Node:
    def __init__(self, data):  # Corrected constructor
        self.data = data
        self.next = None

class Stack:
    def __init__(self):  
        self.top = None

    def push(self, data):
        new_node = Node(data)
        new_node.next = self.top
        self.top = new_node

    def pop(self):
        if self.top is None:
            return None
        popped = self.top.data
        self.top = self.top.next
        return popped

    def display(self):
        current = self.top
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")

# Using the stack
stack = Stack()
stack.push(10)
stack.push(20)

print("Stack elements:")
stack.display()

print("Popped element:", stack.pop())

print("Stack elements after pop:")
stack.display()
