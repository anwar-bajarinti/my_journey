queue = []

# Enqueue
queue.append(10)
queue.append(20)
queue.append(30)

# Dequeue (not efficient)
print(queue.pop(0))  # 10
print(queue)         # [20, 30]
