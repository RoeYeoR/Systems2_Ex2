//315144972
//roeyshmil09@gmail.com

#pragma once

#include <string>
#include <vector>
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
        static Graph reverseGraph(const Graph& g);
        static void DFS(const Vertex& v, std::vector<bool>& visited, const Graph& g);
        static std::vector<int> BFS(const Graph& g, int source, int destination); 
        static std::vector<int> dijkstra(const Graph& g, int source, int destination); 
        static bool isCyclicHelper(const Vertex& v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<Vertex>& cycle); 
        static std::string hasNegativeCycle(const Graph& g,const Vertex& src);
        static std::string isBipartiteHelper(const Graph& g);  
    };

} // namespace ariel