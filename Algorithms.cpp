    //     //315144972
    //     //roeyshmil09@gmail.com

    #include <sstream>
    #include <vector>
    #include <iostream>
    #include <climits>
    #include <queue>
    #include <unordered_set>
    #include <algorithm>
    #include "Graph.hpp"
    #include "Algorithms.hpp"
    #include <limits>

    using namespace std;

    namespace ariel {

    string Algorithms::isConnected(const Graph& g) 
    {

        int n = g.get_adjMatrix().size();
        if (n == 0) return "1";  //An empty graph is trivially connected

        if (!BFS(g, 0)) return "0"; //Check if all nodes are reachable from node 0

        Graph gT = g.getTranspose();
        if (!BFS(gT, 0)) return "0"; //Check if all nodes can reach node 0 in the transposed graph

        return "1";
    }

    bool Algorithms::BFS(const Graph& g, int start) 
    {
        int n = g.get_adjMatrix().size();
        std::vector<bool> visited(n, false);
        std::queue<int> q;

        q.push(start);
        visited[start] = true;
        int visitedCount = 1;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor = 0; neighbor < n; ++neighbor) {
                if (g.get_adjMatrix()[node][neighbor] == 1 && !visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    ++visitedCount;
                }
            }
        }

        return visitedCount == n;
    }

    std::string Algorithms::shortestPath(const Graph& g, int start, int end) {
        if (g.containsNegativeWeights()) {
                return bellmanFord(g, start, end);
            } else {
                return dijkstra(g, start, end);
            }
        }

    std::string Algorithms::dijkstra(const Graph& g, int start, int end) {
        int n = g.get_adjMatrix().size();
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<int> prev(n, -1);
        dist[start] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == end) {
                return addPath(prev, start, end);
            }

            for (int v = 0; v < n; ++v) {
                if (g.get_adjMatrix()[u][v] != 0) {
                    int weight = g.get_adjMatrix()[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        return "-1";
    }

    std::string Algorithms::bellmanFord(const Graph& g, int start, int end) {
        int n = g.get_adjMatrix().size();
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<int> prev(n, -1);
        dist[start] = 0;

        for (int i = 0; i < n-1; ++i) {
            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < n; ++v) {
                    if (g.get_adjMatrix()[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.get_adjMatrix()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.get_adjMatrix()[u][v];
                        prev[v] = u;
                    }
                }
            }
        }

        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (g.get_adjMatrix()[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.get_adjMatrix()[u][v] < dist[v]) {
                    return "-1";
                }
            }
        }

        if (dist[end] == std::numeric_limits<int>::max()) {
            return "-1";
        } else {
            return addPath(prev, start, end);
        }
    }

    std::string Algorithms::addPath(const std::vector<int>& prev, int start, int end) {
        std::vector<int> path;
        for (int at = end; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        if (path.back() != start) return "-1";
        std::reverse(path.begin(), path.end());

        std::ostringstream result;
        for (size_t i = 0; i < path.size(); ++i) {
            if (i != 0) result << "->";
            result << path[i];
        }
        return result.str();
    }


    std::string Algorithms::isContainsCycle(const Graph& g) {
        int n = g.get_adjMatrix().size();
        std::vector<bool> visited(n, false);
        std::vector<int> parent(n, -1);

        // Check for negative cycles using Bellman-Ford
        if (g.containsNegativeWeights() && bellmanFord_DetectCycle(g, parent)) {
            return "The graph contains a negative cycle";
        }

        if(g.get_is_directed())
        {
            // Check for cycles in a directed graph using DFS
        for (int i = 0; i < n; ++i) {
            if (DFS_Directed(g, i, visited, parent)) {
                return addCycle(parent, i);
            }
        }

        }
        else 
        {
            // Check for cycles in an undirected graph using DFS
            for (int i = 0; i < n; ++i) {
            if (!visited[i] && DFS_Undirected(g, i, visited, parent, -1)) {
                return addCycle(parent, i);
            }
        }

        }
        
        return "0";
    }


    bool Algorithms::DFS_Directed(const Graph& g, int v, std::vector<bool>& visited, std::vector<int>& parent) {
        static std::vector<bool> recStack(g.get_adjMatrix().size(), false);
        
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (int u = 0; u < g.get_adjMatrix().size(); ++u) {
                if (g.get_adjMatrix()[v][u] != 0) {
                    if (!visited[u] && DFS_Directed(g, u, visited, parent)) {
                        parent[u] = v;
                        return true;
                    } else if (recStack[u]) {
                        parent[u] = v;
                        return true;
                    }
                }
            }
        }
        recStack[v] = false;
        return false;
    }

    bool Algorithms::DFS_Undirected(const Graph& g, int v, std::vector<bool>& visited, std::vector<int>& parent, int parentVertex) {
        visited[v] = true;

        for (int u = 0; u < g.get_adjMatrix().size(); ++u) {
            if (g.get_adjMatrix()[v][u] != 0) {
                if (!visited[u]) {
                    parent[u] = v;
                    if (DFS_Undirected(g, u, visited, parent, v)) {
                        return true;
                    }
                } else if (u != parentVertex) {
                    parent[u] = v;
                    return true;
                }
            }
        }
        return false;
    }

    bool Algorithms::bellmanFord_DetectCycle(const Graph& g, std::vector<int>& parent) {
        int n = g.get_adjMatrix().size();
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        dist[0] = 0;

        // Relax all edges (n-1) times
        for (int i = 0; i < n - 1; ++i) {
            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < n; ++v) {
                    if (g.get_adjMatrix()[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.get_adjMatrix()[u][v] < dist[v]) {
                        dist[v] = dist[u] + g.get_adjMatrix()[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (g.get_adjMatrix()[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.get_adjMatrix()[u][v] < dist[v]) {
                    return true;
                }
            }
        }

        return false;
    }

    std::string Algorithms::addCycle(const std::vector<int>& parent, int start) {
        std::vector<int> cycle;
        int current = start;

        cycle.push_back(current);
        current = parent[current];
        while (current != start && current != -1) {
            cycle.push_back(current);
            current = parent[current];
        }
        cycle.push_back(start);
        std::reverse(cycle.begin(), cycle.end());

        std::ostringstream result;
        result << "The cycle is: ";
        for (size_t i = 0; i < cycle.size(); ++i) {
            if (i != 0) result << "->";
            result << cycle[i];
        }

        return result.str();
    }


    std::string Algorithms::isBipartite(const Graph& g) {
        int n = g.get_adjMatrix().size();
        std::vector<int> color(n, -1);
        std::unordered_set<int> A, B;

        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!BFS_Bipartite(g, i, color, A, B)) {
                    return "0";
                }
            }
    }

        // Sort in ascending order the vertices in sets A and B
        std::vector<int> sortedA(A.begin(), A.end());
        std::sort(sortedA.begin(), sortedA.end());
        std::vector<int> sortedB(B.begin(), B.end());
        std::sort(sortedB.begin(), sortedB.end());

        // add the output string representing the bipartite sets
        std::ostringstream result;
        result << "The graph is bipartite: A={";
        for (int vertex = 0 ;vertex <sortedA.size()-1; vertex++) {
            result << sortedA[vertex] << ", ";
        }
        result << sortedA[sortedA.size()-1] << "}, B={";

        for (int vertex = 0 ;vertex <sortedB.size()-1; vertex++) {
            result << sortedB[vertex] << ", ";
        }
        result <<sortedB[sortedB.size()-1] << "}";

        return result.str();
    }

    bool Algorithms::BFS_Bipartite(const Graph& g, int start, std::vector<int>& color, std::unordered_set<int>& A, std::unordered_set<int>& B) {
        std::queue<int> q;
        q.push(start);
        color[start] = 0; 
        A.insert(start); 

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < g.get_adjMatrix().size(); ++v) {
                if (g.get_adjMatrix()[u][v] != 0) {
                    // If adjacent vertex v is not colored, color it with opposite color of u
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        if (color[v] == 0) {
                            A.insert(v);
                        } else {
                            B.insert(v);
                        }
                        q.push(v);
                    }
                    // If adjacent vertex v is already colored with the same color as u, then the graph is not bipartite
                    else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    std::string Algorithms::negativeCycle(const Graph& g) {
       
        std::string result = isContainsCycle(g);

        
        if (result == "The graph contains a negative cycle") {
            return result;
        }

        // If no negative cycle is found, return a message indicating this
        return "The graph does not contain any negative cycles";

    }
    } // namespace ariel