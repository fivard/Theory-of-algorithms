#include "Graph.h"

int main() {
    Graph<int, int> graph(true, INF);
    for (int i = 1; i < 5; i++)
        graph.add_vertex(i);

    graph.add_edge(2,1,4);
    graph.add_edge(2,3,1);
    graph.add_edge(2,4,5);
    graph.add_edge(3,4,1);
    graph.add_edge(4,2,1);
    graph.add_edge(4,1,1);

    graph.print();
    graph.Dijkstra(2);
    std::cout << std::endl;
    graph.BellmanFord(2);

    return 0;
}
