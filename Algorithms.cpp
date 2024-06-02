//315144972
//roeyshmil09@gmail.com

#include <sstream>
#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace std;

namespace ariel {

string Algorithms::isConnected(const Graph& g) {
    const Graph& g1 =g;
    int size = g1.get_num_of_vertices();
    if (size <= 1) {
        return "1";
    }

    std::vector<bool> visited(size, false);
    const Vertex& v = g1.get_vertex(0);
    DFS(v, visited,g1);

    if(!g1.get_is_directed())
    {
    for (bool isVisited : visited) 
    {
        if (!isVisited) {
            return "0"; // Graph is not connected
        }
    }
    return "1";

    }
    else
    {

        Graph g2= reverseGraph(g);
        std::fill(visited.begin(), visited.end(), false);
        DFS(v, visited, g2);

    
        for (bool isVisited : visited)
        {
            if (!isVisited)
            {
                return "0"; 
            }
        }

         return "1"; 

    }
   
}

string Algorithms::shortestPath(const Graph& g, int start, int end) {
    if (g.get_is_weighted()) 
    {
        std::vector<int> shortestDistance = dijkstra(g, start, end);
        if (!shortestDistance.empty()) {
            std::string path;
            for (int i = 0; i < shortestDistance.size()-1 ; i++) {
                path += std::to_string(shortestDistance[i]) + "->";
            }
            path += std::to_string(shortestDistance.back());
            return path;
        } else {
            return "-1";
        }
    } else {
        std::vector<int> shortestPath = BFS(g, start, end);
        if (shortestPath.empty()) {
            return "-1"; // No path found
        } else {
            std::string path;
            for (int i = 0; i < shortestPath.size()-1 ; i++) {
                path += std::to_string(shortestPath[i]) + "->";
            }
            path += std::to_string(shortestPath.back());
            return path;
        }
    }
}

string Algorithms::isContainsCycle(const Graph& g) {
    int size = g.get_num_of_vertices();
    std::vector<bool> visited(size, false);
    std::vector<int> parent(size, -1);
    std::vector<Vertex> cycle;
    stringstream result;

    for (Vertex& v : g.get_vertices()) {
        if (!visited[v.get_data()]) {
            if (isCyclicHelper(v, visited, parent, cycle)) {
                result << "The cycle is: ";
                for (int i = cycle.size() - 2; i > 0; --i) {
                    result << cycle[i].get_data() << "->";
                }
                result << cycle[0].get_data() << "->";
                result << cycle[cycle.size() - 1].get_data();
                return result.str();
            }
        }
    }
    return "0"; // No cycle found
}

string Algorithms::isBipartite(const Graph& g) {
    return isBipartiteHelper(g);
}

string Algorithms::negativeCycle(const Graph& g) {
    for (const Vertex& v : g.get_vertices()) {
        std::string cycle = hasNegativeCycle(g, v);
        if (!cycle.empty()) {
            return "Negative cycle found: " + cycle;
        }
    }
    return "No negative cycles found in the graph.";
}

Graph Algorithms::reverseGraph(const Graph& g) {
    Graph reversed;
    bool isExist = false;
    reversed.resetGraph();
    for (int v = 0; v < g.get_num_of_vertices(); v++) {
        for (const Edge& neighbor : g.get_vertex(v).get_neighbours()) {
            for(int i=0;i<reversed.get_num_of_vertices();i++)
            {
                if (neighbor.get_dest().get_data() == reversed.get_vertices()[i].get_data())
                    isExist = true;
            }

            if(!isExist)
                reversed.add_vertex(Vertex(neighbor.get_dest().get_data())); // Ensure the destination vertex is added to the reversed graph
        }
    }
    for (int v = 0; v < g.get_num_of_vertices(); v++) {
        for (const Edge& neighbor : g.get_vertex(v).get_neighbours()) {
            reversed.add_neighbour(reversed.get_vertex(neighbor.get_dest().get_data()), g.get_vertex(v), neighbor.get_weight()); // Reverse the direction of the edge
        }
    }
    return reversed; // Return by value
}



void Algorithms::DFS(const Vertex& v, std::vector<bool>& visited, const Graph& g) {
    visited[v.get_data()] = true;  
    for (const Edge& neighbor : v.get_neighbours()) {
        int neighbor_id = neighbor.get_dest().get_data();
        if (!visited[neighbor_id]) {
            DFS(g.get_vertex(neighbor_id), visited, g);  
        }
    }
}


vector<int> Algorithms::BFS(const Graph& g, int source, int destination) {
    int size = g.get_num_of_vertices();
    vector<int> parent(size, -1);
    vector<bool> visited(size, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == destination) {
            vector<int> shortestPath;
            while (current != -1) {
                shortestPath.push_back(current);
                current = parent[current];
            }
            reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        for (const Edge& e : g.get_vertex(current).get_neighbours()) {
            if (!visited[e.get_dest().get_data()]) {
                visited[e.get_dest().get_data()] = true;
                parent[e.get_dest().get_data()] = current;
                q.push(e.get_dest().get_data());
            }
        }
    }
    return {};
}

std::vector<int> Algorithms::dijkstra(const Graph& g, int source, int destination) {
    int size = g.get_num_of_vertices();
    std::vector<int> dist(size, INT_MAX);
    dist[source] = 0;
    std::vector<int> parent(size, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == destination) {
            std::vector<int> shortestPath;
            int current = destination;
            while (current != -1) {
                shortestPath.push_back(current);
                current = parent[current];
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        for (const Edge& edge : g.get_vertex(u).get_neighbours()) {
            int v = edge.get_dest().get_data();
            int weight = edge.get_weight();

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return {};
}

bool Algorithms::isCyclicHelper(const Vertex& v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<Vertex>& cycle) {
    int v_data = v.get_data();
    visited[v_data] = true;

    for (const Edge& e : v.get_neighbours()) {
        int vertex_id = e.get_dest().get_data();
        if (!visited[vertex_id]) {
            parent[vertex_id] = v_data;
            if (isCyclicHelper(e.get_dest(), visited, parent, cycle))
                return true;
        } else if (vertex_id != parent[v_data]) {
            cycle.push_back(v);
            Vertex cur = v;
            while (cur.get_data() != vertex_id) {
                cur = parent[cur.get_data()];
                cycle.push_back(cur);
            }
            cycle.push_back(e.get_dest());
            return true;
        }
    }
    return false;
}

string Algorithms::hasNegativeCycle(const Graph& g, const Vertex& src) {
        int size = g.get_num_of_vertices();
        std::vector<int> dist(size, INT_MAX);
        std::vector<int> parent(size, -1);
        dist[src.get_data()] = 0;

        // Run Bellman-Ford algorithm
        for (int i = 0; i < size - 1; ++i) {
            for (const Vertex& vertex : g.get_vertices()) {
                int u = vertex.get_data();
                for (const Edge& edge : vertex.get_neighbours()) {
                    int v = edge.get_dest().get_data();
                    int weight = edge.get_weight();
                    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles
        for (const Vertex& vertex : g.get_vertices()) {
            int u = vertex.get_data();
            for (const Edge& edge : vertex.get_neighbours()) {
                int v = edge.get_dest().get_data();
                int weight = edge.get_weight();
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    // Negative cycle detected, reconstruct the cycle
                    std::vector<int> cycle;
                    std::vector<bool> visited(size, false);
                    int x = v;
                    for (int i = 0; i < size; ++i) {
                        x = parent[x];
                    }
                    for (int curr = x; !visited[curr]; curr = parent[curr]) {
                        cycle.push_back(curr);
                        visited[curr] = true;
                    }
                    cycle.push_back(x);
                    std::reverse(cycle.begin(), cycle.end());

                    // Build the cycle string
                    std::string cycleStr;
                    for (int i = 0; i < cycle.size(); ++i) {
                        cycleStr += std::to_string(cycle[i]);
                        if (i < cycle.size() - 1) {
                            cycleStr += "->";
                        }
                    }
                    return cycleStr;
                }
            }
        }

        return ""; // Return empty string if no negative cycle found
    }


string Algorithms::isBipartiteHelper(const Graph& g) {
    int size = g.get_num_of_vertices();
    vector<int> color(size, 0);
    queue<int> q;

    for (int i = 0; i < size; ++i) {
        if (color[i] != 0) continue;
        q.push(i);
        color[i] = 1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (const Edge& e : g.get_vertex(curr).get_neighbours()) {
                int neighbor = e.get_dest().get_data();
                if (color[neighbor] == 0) {
                    color[neighbor] = -color[curr];
                    q.push(neighbor);
                } else if (color[neighbor] == color[curr]) {
                    return "0"; // Graph is not bipartite
                }
            }
        }
    }

    vector<int> group1, group2;
    for (int i = 0; i < size; ++i) {
        if (color[i] == 1) {
            group1.push_back(i);
        } else {
            group2.push_back(i);
        }
    }

    stringstream result;
    result << "The graph is bipartite: A={";
    for (int i = 0; i < group1.size() && i < group1.size() - 1; i++) {
        result << group1[i] << ", ";
    }
        if(group1.size()>0)
        {
            result << group1[group1.size() - 1];
        }
            result<< "}, B={";

    for (int j = 0; j < group2.size() && j < group2.size() - 1; j++) {
        result << group2[j] << ", ";
    }

        if(group2.size()>0)
        {
            result << group2[group2.size() - 1] ;
        }
        result <<  "}";
    

    return result.str(); // Graph is bipartite
}
} 