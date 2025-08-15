from collections import deque

class GraphAdjMatrix:
    def __init__(self, size):
        self.size = size
        self.graph = [[0 for _ in range(size)] for _ in range(size)]

    def add_edge(self, u, v):
        self.graph[u][v] = 1  # For directed graph
        # self.graph[v][u] = 1  # Uncomment for undirected graph

    def display(self):
        for row in self.graph:
            print(row)

    # BFS traversal
    def bfs(self, start):
        visited = [False] * self.size
        queue = deque()

        queue.append(start)
        visited[start] = True

        print("BFS traversal:", end=" ")
        while queue:
            current = queue.popleft()
            print(current, end=" ")

            for i in range(self.size):
                if self.graph[current][i] == 1 and not visited[i]:
                    queue.append(i)
                    visited[i] = True
        print()

    # DFS traversal
    def dfs(self, start):
        visited = [False] * self.size
        print("DFS traversal:", end=" ")
        self._dfs_helper(start, visited)
        print()

    def _dfs_helper(self, node, visited):
        visited[node] = True
        print(node, end=" ")

        for i in range(self.size):
            if self.graph[node][i] == 1 and not visited[i]:
                self._dfs_helper(i, visited)

# ------------------------------
# ✅ Test the graph
# ------------------------------
if __name__ == "__main__":
    g = GraphAdjMatrix(5)
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 3)
    g.add_edge(2, 4)

    print("Adjacency Matrix:")
    g.display()

    g.bfs(0)  # Output: 0 1 2 3 4
    g.dfs(0)  # Output: 0 1 3 2 4
