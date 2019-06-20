#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>	//Biblioteca Padrão
#include <fstream>	//Biblioteca Entrada e saida de arquivos
#include <string>	//Biblioteca de strings
#include <cstdio>
#include <climits>

using namespace std;

class Graph {
	private:
		int num_vertex, num_edges;
		int **matrix_adjacency, **matrix_weights;	
	public:
		Graph();
		~Graph();
		bool insert();				// Insere arestas existentes em um arquivo de texto
		bool insert_edge(int, int);	// Insere aresta manualmente
		bool remove(int, int);		// Remove aresta
		bool full_verify();			// Verifica Grafo
		bool verify_edge(int, int);	// Verifica se uma aresta existe
		void count_edge_vertex();	// Conta arestas e vertices
		void complete_graph();		// Completa um grafo
		void print();				// Imprime Grafo
		void inicialize_weight();	// Inicializa os pesos das arestas
		// void Dijkstra(int src);		// calcula o menor caminho entre um vertice e outro
		// int minDistance(int dist[], bool sptSet[])
};

void menu(int&);

#endif