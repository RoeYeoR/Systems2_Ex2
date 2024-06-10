//315144972
//roeyshmil09@gmail.com

#include <iostream>
#include <sstream>

#include "Graph.hpp"

namespace ariel {

    Graph::Graph() {}
    Graph::Graph(int n) : adjMatrix(n, std::vector<int>(n, 0)) {}


    bool Graph::get_is_directed() const
    {
        return is_directed;
    }

    std::vector<std::vector<int>> Graph::get_adjMatrix() const
    {
        return adjMatrix;
    }

   
    bool Graph::containsNegativeWeights() const{
        int n = adjMatrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j] < 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Graph::isDirected(const std::vector<std::vector<int>>& matrix) const {
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return true; // Asymmetry found, indicating a directed graph
                }
            }
        }
        return false; // No asymmetry found, indicating an undirected graph
    }
        int Graph::countEdges() const {
        int numOfEdges = 0;
        
        for (int i = 0; i < adjMatrix.size(); i++) {
            for (int j = 0; j < adjMatrix.size(); j++) {
                if (adjMatrix[i][j] != 0) {
                numOfEdges++;
                }
            }

        }
        if(!is_directed)
        {
            numOfEdges /=2;
        }
        return numOfEdges;
    }

     Graph Graph::getTranspose() const {
        int n = adjMatrix.size();
        Graph gT(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j] !=0) {
                    gT.adjMatrix[j][i] = adjMatrix[i][j];
                }
            }
        }
        return gT;
    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& adj_Mat) {

        // Check if the matrix is square
        if (adj_Mat.size() != adj_Mat[0].size()) 
        {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        //check if there is a vertex with dist to itself !=0
        for(int i=0; i<adj_Mat.size();i++)
        {
            if(adj_Mat[i][i] != 0)
            {
             throw std::invalid_argument("Invalid graph: At least one vertex with distance to itself != 0.");
            }
        }

        adjMatrix = adj_Mat;
        is_directed = isDirected(adjMatrix);
        numOfVertices = adjMatrix.size();
        numOfEdges = countEdges();


    }

    std::string Graph::printGraph() const {
        std::ostringstream result;
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            if (i != 0) {
                result << "\n";
            }
            result << "[";
            for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
                if (j != 0) {
                    result << ", ";
                }
                result << adjMatrix[i][j];
            }
            result << "]";
        }
        
        return result.str();
        
    }
    bool Graph::containsGraph(const Graph& other) const {
        const std::vector<std::vector<int>>& otherMatrix = other.get_adjMatrix();
        const std::vector<std::vector<int>>& thisMatrix = this->get_adjMatrix();

        // Check if each edge of the other graph exists in this graph
        for (size_t i = 0; i < otherMatrix.size(); ++i) {
            for (size_t j = 0; j < otherMatrix[i].size(); ++j) {
                // If an edge exists in the other graph but not in this graph
                //or value of otherMatrix != value of thisMatrix on the same position, return false
                if (otherMatrix[i][j] != 0 && (i >= thisMatrix.size() || j >= thisMatrix[i].size() || thisMatrix[i][j] != otherMatrix[i][j])) {
                    return false;
                }
            }
        }

        return true;
    }

        // Addition Operator
    Graph Graph::operator+(const Graph& other) const {
        if (this->get_adjMatrix().size() != other.get_adjMatrix().size() || this->get_adjMatrix()[0].size() != other.get_adjMatrix()[0].size()) {
            throw std::invalid_argument("Graphs must be of the same order of magnitude");
        }

        // Create a new graph object
        Graph result;
        result.loadGraph(this->get_adjMatrix()); 
        result += other;
        return result;
    }
    Graph& Graph::operator+=(const Graph& other) {
    if (this->get_adjMatrix().size() != other.get_adjMatrix().size() || this->get_adjMatrix()[0].size() != other.get_adjMatrix()[0].size()) {
            throw std::invalid_argument("Graphs must be of the same order of magnitude");
        }

   
    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; ++j) {
            this->adjMatrix[i][j] += other.adjMatrix[i][j];
        }
    }

    return *this;
}

    // Subtraction Operator
    Graph Graph::operator-(const Graph& other) const {
        if (this->get_adjMatrix().size() != other.get_adjMatrix().size() || this->get_adjMatrix()[0].size() != other.get_adjMatrix()[0].size()) {
            throw std::invalid_argument("Graphs must be of the same order of magnitude");
        }

        Graph result; 
        result.loadGraph(this->adjMatrix);
        result -= other;    
        return result;
    }
    Graph& Graph::operator-=(const Graph& other) {
     if (this->get_adjMatrix().size() != other.get_adjMatrix().size() || this->get_adjMatrix()[0].size() != other.get_adjMatrix()[0].size()) {
            throw std::invalid_argument("Graphs must be of the same order of magnitude");
        }

    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; ++j) {
            this->adjMatrix[i][j] -= other.adjMatrix[i][j];
        }
    }

    return *this;
}

    // Greater Than Operator
    bool Graph::operator>(const Graph& other) const {
       
    if (containsGraph(other)) {
        return true;
    }

    else if (countEdges() > other.countEdges()) {
        return true;
    }
    else {
        // If both graphs have the same number of edges, compare their sizes
        return (get_adjMatrix().size() > other.get_adjMatrix().size());
    }
    
}

    // Greater Than or Equal To Operator
    bool Graph::operator>=(const Graph& other) const {
        // If this graph equals the other graph or this graph is greater than the other graph
        return (*this == other) || (*this > other);
    }

    // Less Than Operator
    bool Graph::operator<(const Graph& other) const {
        
        return !(*this >= other);
    }

    // Less Than or Equal To Operator
    bool Graph::operator<=(const Graph& other) const {
        
        return !(*this > other) || (*this == other);
    }

    // Equality Operator
    bool Graph::operator==(const Graph& other) const {
        
        return this->get_adjMatrix().size() == other.get_adjMatrix().size() 
        //the following == operator refers to std::vector class
        && this->get_adjMatrix() == other.get_adjMatrix();
    }

    // Inequality Operator
    bool Graph::operator!=(const Graph& other) const {

        return !(*this == other);
    }

    
    // Unary Plus Operator
    Graph Graph::operator+() const {
            return *this;
        }

        // Unary Minus Operator
    Graph Graph::operator-() const {
            Graph result(numOfVertices);
            for (int i = 0; i < numOfVertices; ++i) {
                for (int j = 0; j < numOfVertices; ++j) {
                    result.adjMatrix[i][j] = -adjMatrix[i][j];
                }
            }
            return result;
        }

        // Prefix Increment Operator
    Graph& Graph::operator++() {
            for (int i = 0; i < numOfVertices; ++i) {
                for (int j = 0; j < numOfVertices; ++j) {
                     //change only the exists edges
                    if(this->adjMatrix[i][j] !=0)
                    {
                        ++this->adjMatrix[i][j];
                    }
                     
                }
            }
            return *this;
        }

        // Postfix Increment Operator
    Graph Graph::operator++(int) {
            Graph temp(*this); // Create a temporary copy of the current graph
            for (int i = 0; i < this->adjMatrix.size(); ++i) {
                for (int j = 0; j < this->adjMatrix[i].size(); ++j) {
                    if (this->adjMatrix[i][j] != 0) {
                        ++this->adjMatrix[i][j];
                    }
                }
            }
            return temp; // Return the temporary copy
        }

        // Prefix Decrement Operator
    Graph& Graph::operator--() {
            for (int i = 0; i < numOfVertices; ++i) {
                for (int j = 0; j < numOfVertices; ++j) {
                    //change only the exists edges
                    if(this->adjMatrix[i][j] !=0)
                    {
                      --this->adjMatrix[i][j];
                    }
                    
                }
            }
            return *this;
        }

        // Postfix Decrement Operator
    Graph Graph::operator--(int) {
        Graph temp(*this); // Create a temporary copy of the current graph
        for (int i = 0; i < this->adjMatrix.size(); ++i) {
            for (int j = 0; j < this->adjMatrix[i].size(); ++j) {
                if (this->adjMatrix[i][j] != 0) {
                    --this->adjMatrix[i][j];
                }
            }
        }
         return temp; // Return the temporary copy
        }
        // Output Operator
    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
            os << graph.printGraph();
            return os;
        }

   Graph Graph::operator*(const Graph& other) const {
    
    if (this->adjMatrix.size() != other.adjMatrix.size()) {
        throw std::invalid_argument("Cannot multiply graphs with incompatible sizes");
    }

    Graph result(adjMatrix.size());

    // Perform matrix multiplication
    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        for (size_t j = 0; j < other.adjMatrix[0].size(); ++j) {
            int sum = 0;
            for (size_t k = 0; k < adjMatrix[0].size(); ++k) {
                sum += adjMatrix[i][k] * other.adjMatrix[k][j];
            }
            result.adjMatrix[i][j] = sum;
        }
    }

    return result;
}

    // Compound multiplication and assignment operator (*=)
    Graph& Graph::operator*=(int scalar) {
        // Multiply all weights by the scalar
        for (auto& row : adjMatrix) {
            for (auto& weight : row) {
                weight *= scalar;
            }
        }
        return *this; // Return a reference to this object
    }




}
