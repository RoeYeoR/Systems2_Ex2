//315144972
//roeyshmil09@gmail.com

#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Graph.hpp"

namespace ariel {

    class Algorithms {
    public:
        static std::string isConnected(const Graph& g);
        static std::string shortestPath(const Graph& g, int start, int end);
        static std::string isContainsCycle(const Graph& g);
        static std::string isBipartite(const Graph& g);
        static std::string negativeCycle(const Graph& g);

    private:
        static bool BFS(const Graph& g, int start);
        static std::string dijkstra(const Graph& g, int start, int end);
        static std::string bellmanFord(const Graph& g, int start, int end);
        static std::string addPath(const std::vector<int>& prev, int start, int end);
        static bool DFS_Directed(const Graph& g, int v, std::vector<bool>& visited, std::vector<int>& parent);
        static bool DFS_Undirected(const Graph& g, int v, std::vector<bool>& visited, std::vector<int>& parent, int parentVertex);
        static bool bellmanFord_DetectCycle(const Graph& g, std::vector<int>& parent);
        static std::string addCycle(const std::vector<int>& parent, int start);
        static bool BFS_Bipartite(const Graph& g, int start, std::vector<int>& color, std::unordered_set<int>& A, std::unordered_set<int>& B);
    };

} // namespace ariel