#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <queue>
#include <stack>
#include <limits>
#include <fstream>
#include <stdlib.h>

typedef struct Edge	{
	int vertex_A, vertex_B; // Define os valores dos vertices conectados a uma aresta.
	int weight; // Define o peso de uma aresta.
} Edge;

class Graph	{
	private:
		int num_vertex, num_edge;
		int** adjacency_matrix;

        bool BFS(const int&, bool[]) const;
        void permutation(const Graph&, int*, int*, int&, const int&) const;
    
	public:
	    Graph(int);
        ~Graph();

        int number_of_edge() const;
        int number_of_vertex() const;

        int weight(int, int) const;

        bool insert(const Edge&);
        bool remove(const Edge&);
        bool verify_edge(const Edge&) const;
        bool verify_graph() const;
		void complete_graph();
        Graph fill_graph(const int&)  const;
        void BFS(const int&) const;
        void DFS(const int&) const;
		void print() const;
		void save();
        int number_of_component() const;
        void Dijkstra(int, int, int**, int&, int&);
        Graph TSM(const int&, const int&) const;
        Graph MST() const;
};
void menu(int&);

#endif // GRAPH_H
