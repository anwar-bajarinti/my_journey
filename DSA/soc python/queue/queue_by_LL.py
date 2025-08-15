class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class QueueLinkedList:
    def __init__(self):
        self.front = self.rear = None

    def enqueue(self, data):
        new_node = Node(data)
        if not self.rear:
            self.front = self.rear = new_node
        else:
            self.rear.next = new_node
            self.rear = new_node

    def dequeue(self):
        if not self.front:
            return "Queue is empty"
        result = self.front.data
        self.front = self.front.next
        if not self.front:
            self.rear = None
        return result

    def display(self):
        temp = self.front
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("None")
print("Queue using Linked List:")
q = QueueLinkedList()
q.enqueue(1)
q.enqueue(2)
q.enqueue(3)
q.display()           # 1 -> 2 -> 3 -> None
print(q.dequeue())    # 1
q.display()           # 2 -> 3 -> None
