#include "Graph.h"

int main() {
    Graph<int, int> graph(true);
    for (int i = 1; i < 6; i++)
        graph.add_vertex(i);

    graph.add_edge(1,2,-1);
    graph.add_edge(1,3,4);
    graph.add_edge(2,3,3);
    graph.add_edge(2,4,2);
    graph.add_edge(2,5,2);
    graph.add_edge(4,2,1);
    graph.add_edge(4,3,5);
    graph.add_edge(5,4,-3);

    graph.print();
    graph.BellmanFord(1);

    return 0;
}
