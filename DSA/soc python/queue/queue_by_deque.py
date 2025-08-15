from collections import deque

queue = deque()

# Enqueue
queue.append(10)
queue.append(20)
queue.append(30)

# Dequeue
print(queue.popleft())  # 10
print(queue)            # deque([20, 30])
