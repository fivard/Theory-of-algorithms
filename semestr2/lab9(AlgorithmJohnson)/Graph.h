//
// Created by Acer on 01.05.2021.
//

#ifndef LAB9_ALGORITHMJOHNSON__GRAPH_H
#define LAB9_ALGORITHMJOHNSON__GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include "../lab8(FibonacciHeap)/FibonacciHeap.h"

#define vert first
#define dist second

template <class T, class D>
class Graph{
    std::map<T, std::map<T, D>> graph;
    bool directed;
    D inf;
public:
    Graph(bool _directed, D _inf): directed(_directed),
                                            inf(_inf){};
    ~Graph() = default;

    //-----------------------Basically-----------------------//

    void add_vertex(T new_vertex){
        if ( graph.template find( new_vertex ) == graph.end() )
            graph[new_vertex] = {};
        else
            std::cout << "This vertex [" << new_vertex <<"] is already exists\n";
    }
    void add_edge(T from_vertex, T to_vertex, D distance){
        if (graph.template find(from_vertex) == graph.end()){
            std::cout << "First vertex [" << from_vertex <<"] doesn't exist\n";
            return;
        }
        if (graph.template find(to_vertex) == graph.end()){
            std::cout << "Second vertex [" << to_vertex << "] doesn't exist\n";
            return;
        }

        auto edges = graph[from_vertex];
        if ( edges.find(to_vertex) == edges.end()) {

            graph[from_vertex][to_vertex] = distance;

            if (!directed)
                graph[to_vertex][from_vertex] = distance;
        } else {
            std::cout << "This edge already exists\n";
        }
    }
    void delete_vertex(T deleted_vertex) {
        if (graph.template find(deleted_vertex) != graph.end()){
            graph.erase(deleted_vertex);
            for (auto &item : graph) {
                item.second.erase(deleted_vertex);
            }
        } else {
            std::cout << "This vertex doesn't exist\n";
        }
    }
    void delete_edge(T from_vertex, T to_vertex){
        if (graph.template find(from_vertex) == graph.end()){
            std::cout << "First vertex [" << from_vertex <<"] doesn't exist\n";
            return;
        }
        if (graph.template find(to_vertex) == graph.end()){
            std::cout << "Second vertex [" << to_vertex << "] doesn't exist\n";
            return;
        }

        auto& edges_from = graph[from_vertex];
        if ( edges_from.find(to_vertex) != edges_from.end())
            edges_from.erase(to_vertex);
        else
            std::cout << "This edge [" << from_vertex << ", " << to_vertex << "] doesn't exist\n";

        if (!directed) {
            auto& edges_to = graph[to_vertex];
            edges_to.erase(from_vertex);
        }
    }
    void print() const{
        std::cout << "\nGraph:\n";
        for (auto &item : graph){
            std::cout << item.first << ": ";
            for (auto edge : item.second)
                std::cout << "->" << edge.vert << " = " << edge.dist << '\t';
            std::cout << std::endl;
        }
        std::cout << '\n';
    }

    //-----------------------Algorithm------------------------//

    std::map<T, D> BellmanFord(T start_vertex){
        std::map<T, D> distance;

        for (auto& item : graph)
            distance[item.vert] = inf;
        distance[start_vertex] = 0;

        for (int i = 0; i < graph.size() - 1; i++){
            for (auto& vertex : graph)
                for (auto& edges : vertex.dist){
                    if (distance[edges.vert] > distance[vertex.vert] + edges.dist)
                        distance[edges.vert] = distance[vertex.vert] + edges.dist;
                }
        }

        for (auto& vertex : graph)
            for (auto& edges : vertex.dist){
                if (distance[edges.vert] > distance[vertex.vert] + edges.dist)
                    std::cout << "Graph contains negative weight cycle\n";
            }

        for (auto& item : distance)
            std::cout << item.vert << '\t' << item.dist << std::endl;
        return distance;
    }
    std::map<T, D> Dijkstra(T start_vertex){
        std::map<T, bool> used;
        std::map<T, D> distance;
        FibonacciHeap< std::pair<D, T> > heap;

        for (auto item : graph) {
            used[item.vert] = false;
            distance[item.vert] = inf;
        }
        distance[start_vertex] = 0;

        heap.insert({0, start_vertex});
        while (!heap.empty()){
            T min_vertex = heap.minimum()->values().second;
            heap.extractMin();

            if (distance[min_vertex] == inf)
                break;

            used[min_vertex] = true;
            for (auto& item : graph[min_vertex]){
                if (distance[item.vert] > distance[min_vertex] + item.dist)
                    distance[item.vert] = distance[min_vertex] + item.dist;

                if (!used[item.vert])
                    heap.insert({distance[item.vert], item.vert});
            }
        }

        for (auto& item : distance)
            std::cout << item.vert << '\t' << item.dist << std::endl;
        return distance;
    }

    std::map<T, std::map<T, D>>{

    };


};

template <class T, class D>
std::ostream& operator<< (std::ostream &out, const std::pair<T, D> pair){
    out << pair.first << ":" << pair.second;
    return out;
}

#endif //LAB9_ALGORITHMJOHNSON__GRAPH_H
