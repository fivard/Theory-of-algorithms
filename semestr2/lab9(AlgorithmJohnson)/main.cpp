#include "Graph.h"

int main() {
    Graph<int, int> graph(true, INF);
    for (int i = 1; i < 5; i++)
        graph.add_vertex(i);

    graph.add_edge(1,2,-2);
    graph.add_edge(1,3,7);
    graph.add_edge(1,4,5);
    graph.add_edge(2,3,8);
    graph.add_edge(2,4,6);
    graph.add_edge(3,2,3);
    graph.add_edge(3,4,-4);
    graph.add_edge(4,1,-1);

    graph.print();

    graph.Johnson();

    return 0;
}
