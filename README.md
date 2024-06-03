

## Class: Graph

### Private Members:
- `bool is_directed`: Indicates whether the graph is directed or undirected.
- `int numOfVertices`: Number of vertices in the graph.
- `int numOfEdges`: Number of edges in the graph.
- `std::vector<std::vector<int>> adjMatrix`: Adjacency matrix representing the graph.

### Public Members:
- `Graph()`: Default constructor.
- `Graph(int n)`: Constructor initializing the adjacency matrix with size `n x n`.
- `bool get_is_directed() const`: Returns whether the graph is directed or not.
- `std::vector<std::vector<int>> get_adjMatrix() const`: Returns the adjacency matrix of the graph.
- `int countEdges() const`: Returns the total number of edges in the graph.
- `bool containsNegativeWeights() const`: Checks if the graph contains negative weights.
- `bool isDirected(const std::vector<std::vector<int>>& matrix) const`: Checks if the given adjacency matrix represents a directed graph.
- `Graph getTranspose() const`: Returns the transpose of the graph.
- `void loadGraph(const std::vector<std::vector<int>>& adj_Mat)`: Loads the graph from a given adjacency matrix.
- `std::string printGraph() const`: Returns a string representation of the graph.
- `bool containsGraph(const Graph& other) const`: Checks if the graph contains another graph.
- `Graph operator+(const Graph& other) const`: Performs addition of two graphs.
- `Graph& operator+=(const Graph& other)`: Performs in-place addition of two graphs.
- `Graph operator-(const Graph& other) const`: Performs subtraction of two graphs.
- `Graph& operator-=(const Graph& other)`: Performs in-place subtraction of two graphs.
- `Graph operator+() const`: Unary positive operator.
- `Graph operator-() const`: Unary negative operator.
- `bool operator>(const Graph& other) const`: Greater than operator.
- `bool operator>=(const Graph& other) const`: Greater than or equal to operator.
- `bool operator<(const Graph& other) const`: Less than operator.
- `bool operator<=(const Graph& other) const`: Less than or equal to operator.
- `bool operator==(const Graph& other) const`: Equality operator.
- `bool operator!=(const Graph& other) const`: Inequality operator.
- `Graph& operator++()`: Prefix increment operator.
- `Graph operator++(int)`: Postfix increment operator.
- `Graph& operator--()`: Prefix decrement operator.
- `Graph operator--(int)`: Postfix decrement operator.
- `Graph operator*(const Graph& other) const`: Scalar multiplication operator.
- `Graph& operator*=(int scalar)`: Scalar multiplication assignment operator.
- `friend std::ostream& operator<<(std::ostream& os, const Graph& graph)`: Overloaded stream insertion operator for output.

---

# Algorithms.hpp

## Class: Algorithms

### Public Static Methods:
- `static std::string isConnected(const Graph& g)`: Checks if the graph is connected.
- `static std::string shortestPath(const Graph& g, int start, int end)`: Finds the shortest path between two vertices.
- `static std::string isContainsCycle(const Graph& g)`: Checks if the graph contains a cycle.
- `static std::string isBipartite(const Graph& g)`: Checks if the graph is bipartite.
- `static std::string negativeCycle(const Graph& g)`: Detects negative cycles in the graph.

### Private Static Methods:
- `static bool BFS(const Graph& g, int start)`: Breadth-first search for graph traversal.
- `static std::string dijkstra(const Graph& g, int start, int end)`: Dijkstra's algorithm for finding shortest paths.
- `static std::string bellmanFord(const Graph& g, int start, int end)`: Bellman-Ford algorithm for finding shortest paths with negative weights.
- `static std::string addPath(const std::vector<int>& prev, int start, int end)`: Utility function to add path from previous array.
- `static bool DFS_Directed(const Graph& g, int v, std::vector<bool>& visited, std::vector<int>& parent)`: Depth-first search for directed graphs.
- `static bool DFS_Undirected(const Graph& g, int v, std::vector<bool>& visited, std::vector<int>& parent, int parentVertex)`: Depth-first search for undirected graphs.
- `static bool bellmanFord_DetectCycle(const Graph& g, std::vector<int>& parent)`: Helper function to detect cycles using Bellman-Ford algorithm.
- `static std::string addCycle(const std::vector<int>& parent, int start)`: Utility function to add cycle from parent array.
- `static bool BFS_Bipartite(const Graph& g, int start, std::vector<int>& color, std::unordered_set<int>& A, std::unordered_set<int>& B)`: Breadth-first search to check bipartiteness.

