class GraphAdjMatrix:
    def __init__(self, size):  # ✅ Corrected __init__
        self.size = size
        self.graph = [[0 for _ in range(size)] for _ in range(size)]

    def add_edge(self, u, v):
        self.graph[u][v] = 1  # For undirected: also set self.graph[v][u] = 1

    def display(self):
        for row in self.graph:
            print(row)

# ---------------------------
# ✅ Test the graph
# ---------------------------
if __name__ == "__main__":
    g = GraphAdjMatrix(4)
    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(3, 0)

    print("Adjacency Matrix:")
    g.display()
