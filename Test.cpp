#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <sstream>


using namespace std;

TEST_CASE("Test graph addition")
{
    
    ariel::Graph g1;
    
    
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g1.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g1) == "0");

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {1, 0, 0}};
    g2.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g2) == "0");

    ariel::Graph g3 = g1 + g2;
    
    CHECK(g3.printGraph() == "[0, 1, 0]\n[0, 0, 1]\n[1, 0, 0]");
    CHECK(ariel::Algorithms::isConnected(g3) == "1");
}

TEST_CASE("Test graph addition and assignment")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g1.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g1) == "1");

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, -2, -1},
        {-2, 0, -1},
        {-1, -1, 0}};
    g2.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g2) == "1");

    g1 += g2;

    CHECK(g1.printGraph() == "[0, 0, 0]\n[0, 0, 2]\n[0, 2, 0]");
    CHECK(ariel::Algorithms::isConnected(g1) == "0");
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 3, 6},
        {3, 0, 2},
        {6, 2, 0}};
    g1.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g1,0,2) == "0->1->2");

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 5},
        {2, 0, 1},
        {5, 1, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 - g2;

    CHECK(g3.printGraph() == "[0, 1, 1]\n[1, 0, 1]\n[1, 1, 0]");
    CHECK(ariel::Algorithms::shortestPath(g3,0,2) == "0->2");
}

TEST_CASE("Test graph subtraction and assignment")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 0},
        {2, 0, 3},
        {0, 3, 0}};
    g1.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g1)== "The graph is bipartite: A={0, 2}, B={1}");

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, -1},
        {2, 0, 1},
        {-1, 1, 0}};
    g2.loadGraph(graph2);

    g1 -= g2;

    CHECK(g1.printGraph() == "[0, 0, 1]\n[0, 0, 2]\n[1, 2, 0]");
    CHECK(ariel::Algorithms::isBipartite(g1)== "The graph is bipartite: A={0, 1}, B={2}");
}

TEST_CASE("Test unary plus operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2 = +g1; 

   
    CHECK(g1 == g2); // unary plus does not change the value
}

TEST_CASE("Test unary minus operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g1) == "The graph does not contain any negative cycles");

    ariel::Graph g2 = -g1; // unary minus turns the sign of the value

    ariel::Graph expectedGraph;
    vector<vector<int>> expected = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    expectedGraph.loadGraph(expected);

    CHECK(g2 == expectedGraph);
    CHECK(ariel::Algorithms::negativeCycle(g2) == "The graph contains a negative cycle");
}


TEST_CASE("Test less than operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}
TEST_CASE("Test less than or equal to operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 <= g2);
}
TEST_CASE("Test equality operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
}
TEST_CASE("Test inequality operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}
TEST_CASE("Test prefix increment operator")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    ++g; // increment the value by 1 before it is used in  an expression

    CHECK(g.printGraph() == "[1, 2, 1]\n[2, 1, 2]\n[1, 2, 1]");
}
TEST_CASE("Test postfix increment operator")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    g++; // increment the value by 1 after it is used in an expression

    CHECK(g.printGraph() == "[1, 2, 1]\n[2, 1, 2]\n[1, 2, 1]");
}
TEST_CASE("Test prefix decrement operator")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    g.loadGraph(graph);

    --g;

    CHECK(g.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}
TEST_CASE("Test postfix decrement operator")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    g.loadGraph(graph);

    g--;

    CHECK(g.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}



TEST_CASE("Test prefix and postfix increment operators")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    // Test prefix increment (++g)
    ariel::Graph g_prefix_inc = ++g;
    CHECK(g_prefix_inc == g);

    // Test postfix increment (g++)
    ariel::Graph g_postfix_inc = g++;
    CHECK(g_postfix_inc != g); 
}


TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 * g2;

    CHECK(g3.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}

TEST_CASE("Test graph multiplication and assignment")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    g *= 2;

    CHECK(g.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

