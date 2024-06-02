//315144972
//roeyshmil09@gmail.com

#include <iostream>
#include <vector>
    
#include "Graph.hpp"

namespace ariel {
    // Vertex class methods

    Vertex::Vertex(int data) : data(data) {}

    int Vertex::get_data() const {
        return data;
    }

    const std::vector<Edge>& Vertex::get_neighbours() const{
        return neighbours;
    }

    std::vector<Edge>& Vertex::get_neighbours() {
        return neighbours;
    }

    // Edge class methods
    Edge::Edge(const Vertex& dest, int weight) : dest(dest), weight(weight) {}

    const Vertex& Edge::get_dest() const {
        return dest;
    }

    int Edge::get_weight() const {
        return weight;
    }

    // Graph class methods
    Graph::Graph() : countVertices(0), countEdges(0), isWeighted(false), isDirected(false) {
        vertices.clear();
    }

    std::vector<Vertex> Graph::get_vertices() const {
        return vertices;
    }

    int Graph::get_num_of_vertices() const {
        return countVertices;
    }

        int Graph::get_num_of_edges() const
        {
        return countEdges;
        }

    const Vertex& Graph::get_vertex(int data) const {
        if (data >= 0 && data < vertices.size()) {
            return vertices[data];
        } 
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    void Graph::set_is_weighted(bool flag) {
        isWeighted = flag;
    }

    void Graph::set_is_directed(bool flag) {
        isDirected = flag;
    }

    bool Graph::get_is_weighted() const {
        return isWeighted;
    }

    bool Graph::get_is_directed() const {
        return isDirected;
    }

    void Graph::add_vertex(const Vertex& v) {
        vertices.push_back(v);
        countVertices++;
    }

    void Graph::add_neighbour(const Vertex& source,const Vertex& dest, int weight) {
        if (source.get_data() < vertices.size() && source.get_data() >=0) {
            Edge e(dest, weight);
            vertices[source.get_data()].get_neighbours().push_back(e);
        } else {
            throw std::out_of_range("Source index out of range");
        }
    }

    std::string Graph::printGraph() const {
       std::string output;
            
            for (size_t i = 0; i < vertices.size(); ++i) {
                const std::vector<ariel::Edge>& row = vertices[i].get_neighbours();
                output += "[";
                for (size_t j = 0; j < row.size(); ++j) {
                    output += std::to_string(row[j].get_weight());
                    if (j < row.size() - 1) {
                        output += ", ";
                    }
                }
                output += "]";
                if (i < vertices.size() - 1) {
                    output += "\n";
                }
            }
            
            return output;
    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& adj_Mat) {

        resetGraph();
        
        //check for squared matrix 
        int numRows = adj_Mat.size();

        // Check if all rows have the same number of columns
        for (std::vector<int> row : adj_Mat) 
        {
            if (row.size() != numRows)
            {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
    
        for (int i = 0; i < adj_Mat.size(); ++i) {
            Vertex v(i);
            add_vertex(v);
        }

        for (int j = 0; j < adj_Mat.size(); ++j) {
            const Vertex& source = get_vertex(j);
            for (int k = 0; k < adj_Mat.size(); ++k) {
                if (adj_Mat[j][k] != adj_Mat[k][j]) {
                    set_is_directed(true);
                }

                if (adj_Mat[j][k] > 1) {
                    set_is_weighted(true);
                }
            
                // if(adj_Mat[j][k] > 0)
                // {
                    const Vertex& dest = get_vertex(k);
                    //if(source.get_data() != dest.get_data())
                    add_neighbour(source, dest, adj_Mat[j][k]);

               //}
              
                
            }

        }

        if(isDirected)
          countEdges = countEdgesDirected(adj_Mat);
        else    
           countEdges =  countEdgesUndirected(adj_Mat);            
    }

void Graph::resetGraph()
{
    countVertices = 0;
    countEdges = 0;
    isWeighted = false;
    isDirected = false;
    vertices.clear();

}

int Graph::countEdgesDirected(const std::vector<std::vector<int>>& adj_Mat)
{
    int numVertices = adj_Mat.size();
    int edgeCount = 0;
    
    // Count all the edges in the matrix
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adj_Mat[i][j] != 0) {
                edgeCount++;
            }
        }
    }
    return edgeCount;


}

int Graph::countEdgesUndirected(const std::vector<std::vector<int>>& adj_Mat)
{
    int numVertices = adj_Mat.size();
    int edgeCount = 0;
    
    // Count the number of edges in the upper triangle of the matrix
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (adj_Mat[i][j] != 0) {
                edgeCount++;
            }
        }
    }
    return edgeCount;

}

 std::vector<std::vector<int>> Graph::toAdjacencyMatrix(const Graph& other) const 
    {

        std::vector<std::vector<int>> adjMatrix(other.get_num_of_vertices(),
        std::vector<int>(other.get_num_of_vertices(), 0));

        for (const Vertex& v : other.vertices) {
            int src = v.get_data();
            for (const Edge& e : v.get_neighbours()) {
                int dest = e.get_dest().get_data();
                adjMatrix[src][dest] = e.get_weight();
            }
        }

        return adjMatrix;
    }

        bool Graph::isContained(std::vector<std::vector<int>>& matrix1,std::vector<std::vector<int>>& matrix2) const
        {
            int minSize = matrix1.size() < matrix2.size() ?  matrix1.size()  : matrix2.size();
            
            for (size_t i = 0; i < minSize; i++)
            {
                for (size_t j = 0; j < minSize; j++)
                {
                   if((matrix1[i][j] < matrix2[i][j]))
                   {
                        return false;

                   }
                }
                
            }
            
            return true;


        }

         bool Graph::SameSize(const Graph& g1,const Graph& g2) const
         {

            return (g1.get_num_of_vertices() == g2.get_num_of_vertices());

         }
    
        Graph Graph::operator+(const Graph& other) const
        {
            
            if(!SameSize(*this,other))
            {
                throw std::invalid_argument("Not the same size !");
            }

            std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
            std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

            std::vector<std::vector<int>>resultMatrix(matrix1.size(), std::vector<int>(matrix1.size(), 0));
            for(int i=0;i<resultMatrix.size();i++)
            {
                for(int j=0;j<resultMatrix.size();j++)
                {
                    resultMatrix[i][j] = matrix1[i][j] +  matrix2[i][j];
                }
            }

            Graph g3;
            g3.loadGraph(resultMatrix);
            return g3;
        }

        Graph Graph::operator*(const Graph& other) const
        {
        if(!SameSize(*this,other))
            {
                throw std::invalid_argument("Not the same size !");
            }
            // Convert the graphs to adjacency matrices
        std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

        
        std::vector<std::vector<int>> resultMatrix(countVertices, std::vector<int>(countVertices, 0));

    
        for (int i = 0; i < countVertices; ++i) {
            for (int j = 0; j < countVertices; ++j) {
                for (int k = 0; k < countVertices; ++k) {
                    resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        Graph resultGraph;
        resultGraph.loadGraph(resultMatrix);
        return resultGraph;


        }
    // Operator +=
    Graph& Graph::operator+=(const Graph& other) {
        if (!SameSize(*this, other)) {
            throw std::invalid_argument("Not the same size !");
        }

        std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1.size(); ++j) {
                matrix1[i][j] += matrix2[i][j];
            }
        }

        this->loadGraph(matrix1);
        return *this;
    }
    // unary plus operator
        Graph Graph::operator+() const {
            // Unary plus returns a copy of the current graph
            return *this;
        }

        // unary minus operator
        Graph Graph::operator-() const {
            std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);

            for (size_t i = 0; i < adjMatrix.size(); ++i) {
                for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                    adjMatrix[i][j] = -adjMatrix[i][j];
                }
            }

            Graph result;
            result.loadGraph(adjMatrix);
            return result;
        }

    // Operator -
    Graph Graph::operator-(const Graph& other) const {
        if (!SameSize(*this, other)) {
            throw std::invalid_argument("Not the same size !");
        }

        std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1.size(); ++j) {
                matrix1[i][j] -= matrix2[i][j];
            }
        }

        Graph result;
        result.loadGraph(matrix1);
        return result;
    }

    // Operator -=
    Graph& Graph::operator-=(const Graph& other) {
        if (!SameSize(*this, other)) {
            throw std::invalid_argument("Not the same size !");
        }

        std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1.size(); ++j) {
                matrix1[i][j] -= matrix2[i][j];
            }
        }

        loadGraph(matrix1);
        return *this;
    }

    // Prefix increment
    Graph& Graph::operator++() {
        
        std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);
    
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                ++adjMatrix[i][j];
            }
        }
        loadGraph(adjMatrix);
        return *this;
    }

    // Postfix increment
    Graph Graph::operator++(int) {
        
        Graph copy(*this);
    
        std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);
    
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                ++adjMatrix[i][j];
            }
        }
        
        loadGraph(adjMatrix);
        return copy;
    }

    // Prefix decrement
    Graph& Graph::operator--() {
    
        std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);
    
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                --adjMatrix[i][j];
            }
        }
    
        loadGraph(adjMatrix);
        return *this;
    }

    // Postfix decrement
    Graph Graph::operator--(int) {
        // Create a copy of the current graph
        Graph copy(*this);
       
        std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);
        // Decrement all elements of the adjacency matrix
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                --adjMatrix[i][j];
            }
        }
        
        loadGraph(adjMatrix);
        return copy;
    }
    // Multiply the graph by a scalar
    Graph& Graph::operator*=(int scalar) {
        
        std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);
        // Multiply all elements of the adjacency matrix by the scalar
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                adjMatrix[i][j] *= scalar;
            }
        }
        // Update the graph with the multiplied adjacency matrix
        loadGraph(adjMatrix);
        return *this;
    }

    // Divide the graph by a scalar
    Graph& Graph::operator/=(int scalar) {
       
        std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);
        // Check if the scalar is zero
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero!");
        }
        // Divide all elements of the adjacency matrix by the scalar
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                adjMatrix[i][j] /= scalar;
            }
        }
        // Update the graph with the divided adjacency matrix
        loadGraph(adjMatrix);
        return *this;
    }

  // Operator for checking if one graph is equal to the other
    bool Graph::operator==(const Graph& other) const 
    {
        if(this->get_num_of_vertices() != other.get_num_of_vertices())
        {
            return false;
        }

        std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

        for (size_t i = 0; i < matrix1.size(); i++)
        {
            for (size_t j = 0; j < matrix1.size(); j++)
            {
            if(matrix1[i][j] != matrix2[i][j])
            {
                return false;
            }
            }
            

        }

        return true;
        
    }

bool Graph::operator>(const Graph& other) const 
{

    std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
    std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

    if(isContained(matrix1,matrix2))
    {
        return true;
    }

    if(!(*this == other))
    {

    if(this->get_num_of_edges() > other.get_num_of_edges())
    {
        
      return true;
        
    }

    else if(this->get_num_of_vertices() > other.get_num_of_vertices())
    {
        return true;
    }

    }

    return false;
}

bool Graph::operator<=(const Graph& other) const
{

    return (!(*this > other) || (*this==other));

}
    
bool Graph::operator>=(const Graph& other) const
{
    return (!(*this < other) || (*this==other));

}

bool Graph::operator<(const Graph& other) const
{
    return (!(*this > other) && !(*this ==other));  

}

bool Graph::operator!=(const Graph& other) const
{
    return !(*this ==other);

}

std::ostream& operator<<(std::ostream& os, const Graph& g) 
{
       os << g.printGraph() << std::endl;
} 



}