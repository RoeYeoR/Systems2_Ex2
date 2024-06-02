Systems Programming B - C++ Programming: Graph Project
This repository contains the project assignment for the Systems Programming B course at Ariel University. The project focuses on implementing classes and algorithms related to graphs in C++.

Project Description
In this project, I implemented a Graph class to represent graphs using an adjacency matrix. The Graph class supports both directed and undirected graphs, as well as weighted and unweighted graphs. Additionally, we implement various algorithms to perform operations on graphs, such as determining connectivity, finding shortest paths, detecting cycles, and checking for bipartiteness.

Files
Graph.hpp: Header file containing the declaration of the Graph class and related classes (Vertex and Edge).
Graph.cpp: Implementation file for the Graph class.
Algorithms.hpp: Header file containing declarations for the Algorithms namespace, which provides implementations for various graph algorithms.
Algorithms.cpp: Implementation file for the Algorithms namespace.
Demo.cpp: Contains demo examples demonstrating how to use the Graph class and algorithms.
Classes and Algorithms
Graph Class
Vertex: Represents a vertex in the graph.
Edge: Represents an edge connecting two vertices.
Graph: Represents a graph using an adjacency matrix. It includes methods to add vertices and edges, load graphs from adjacency matrices, print graphs, and access graph properties. Additional methods include:
set_is_weighted: Sets whether the graph is weighted.
set_is_directed: Sets whether the graph is directed.
countEdgesUndirected: Counts the number of edges in an undirected graph.
countEdgesDirected: Counts the number of edges in a directed graph.
resetGraph: Resets the graph to its initial state.
isContained: Checks if one adjacency matrix is contained within another.
toAdjacencyMatrix: Converts another graph into an adjacency matrix.
SameSize: Checks if two graphs have the same size.
operator+: Adds two graphs together.
operator+=: Adds another graph to the current graph.
operator-: Subtracts another graph from the current graph.
operator-=: Subtracts another graph from the current graph.
operator+: Unary plus operator.
operator-: Unary minus operator.
operator>: Greater than operator.
operator>=: Greater than or equal to operator.
operator<: Less than operator.
operator<=: Less than or equal to operator.
operator==: Equal to operator.
operator!=: Not equal to operator.
operator++: Prefix increment operator.
operator++: Postfix increment operator.
operator--: Prefix decrement operator.
operator--: Postfix decrement operator.
operator<<: Output stream operator.
operator*: Multiplies the graph by a scalar.
*operator=**: Multiplies the graph by a scalar (in-place).
operator/=: Divides the graph by a scalar (in-place).
Algorithms
isConnected: Determines if a graph is connected.
shortestPath: Finds the shortest path between two vertices in a graph.
isContainsCycle: Checks if a graph contains any cycles.
isBipartite: Determines if a graph is bipartite.
negativeCycle: Finds a negative cycle in a graph (if it exists).
DFS: Depth-first search algorithm implementation.
BFS: Breadth-first search algorithm implementation.
dijkstra: Dijkstra's algorithm for finding shortest paths.
