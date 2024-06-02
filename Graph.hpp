//315144972
//roeyshmil09@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept>

namespace ariel {

    class Edge;
    class Vertex;
    class Graph;

    class Vertex {
    private:
        int data;
        std::vector<Edge> neighbours;

    public:
        Vertex(int data);
        int get_data() const;
        const std::vector<Edge>& get_neighbours() const;
        std::vector<Edge>& get_neighbours();
    
    };
    

    class Edge {
    private:
        const Vertex& dest;
        int weight;

    public:
        Edge(const Vertex& dest, int weight);
        const Vertex& get_dest() const;
        int get_weight() const;
    };

    class Graph {
    private:
        int countVertices;
        int countEdges;
        std::vector<Vertex> vertices;
        bool isWeighted;
        bool isDirected;

    public:
        Graph();
        std::vector<Vertex> get_vertices() const;
        int get_num_of_vertices() const;
        int get_num_of_edges() const;
        const Vertex& get_vertex(int data) const;
        void set_is_weighted(bool flag);
        void set_is_directed(bool flag);
        bool get_is_weighted() const;
        bool get_is_directed() const;
        int countEdgesUndirected(const std::vector<std::vector<int>>& adj_Mat);
        int countEdgesDirected(const std::vector<std::vector<int>>& adj_Mat);
        void add_vertex(const Vertex& v);
        void add_neighbour(const Vertex& source,const Vertex& dest, int weight);
        void loadGraph(const std::vector<std::vector<int>>& adj_Mat);
        std::string printGraph() const;
        void resetGraph();
        bool isContained(std::vector<std::vector<int>>& matrix1,std::vector<std::vector<int>>& matrix2) const;
        std::vector<std::vector<int>> toAdjacencyMatrix(const Graph& other) const;
        bool SameSize(const Graph& g1,const Graph& g2)const;
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
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
        Graph operator*(const Graph& other) const;
        Graph& operator*=(int scalar); 
        Graph& operator/=(int scalar); 
    };

} 

#endif // GRAPH_HPP