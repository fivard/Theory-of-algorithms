#include "Graph.h"

int main() {
    Graph<int, int> graph(true);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2, 3);
    graph.print();

    graph.delete_edge(1,2);
    graph.print();
    return 0;
}
