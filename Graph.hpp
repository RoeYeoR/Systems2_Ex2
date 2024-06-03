//315144972
//roeyshmil09@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept>

namespace ariel {


    class Graph {
        private:
            bool is_directed;
            int numOfVertices;
            int numOfEdges;
            std::vector<std::vector<int>> adjMatrix;

        public:
            Graph();
            Graph(int n) : adjMatrix(n, std::vector<int>(n, 0)) {}

            bool get_is_directed() const;
            std::vector<std::vector<int>> get_adjMatrix() const;
            int countEdges() const;
            bool containsNegativeWeights() const;   
            bool isDirected(const std::vector<std::vector<int>>& matrix) const;
            Graph getTranspose() const;

            void loadGraph(const std::vector<std::vector<int>>& adj_Mat);
            std::string printGraph() const;
            

            bool containsGraph(const Graph& other) const;
            Graph operator+(const Graph& other) const;
            Graph& operator+=(const Graph& other);
            Graph operator-(const Graph& other) const;
            Graph& operator-=(const Graph& other);
            Graph operator+() const; 
            Graph operator-() const; 
            bool operator>(const Graph& other) const;
            bool operator>=(const Graph& other) const;
            bool operator<(const Graph& other) const;
            bool operator<=(const Graph& other) const;
            bool operator==(const Graph& other) const;
            bool operator!=(const Graph& other) const;
            Graph& operator++(); 
            Graph operator++(int); 
            Graph& operator--(); 
            Graph operator--(int); 
            Graph operator*(const Graph& other) const;
            Graph& operator*=(int scalar); 
            friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    };

} 

#endif // GRAPH_HPP