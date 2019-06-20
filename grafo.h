#IFNDEF GRAFO_H
#DEFINE GRAFO_H

#include <iostream>	//Biblioteca Padrão
#include <fstream>	//Biblioteca Entrada e saida de arquivos
#include <string>	//Biblioteca de strings

class Graph {
		int num_vertex;
		int num_edges;
		int** matrix_adjacency;
		int** matrix_weights;
	
	public:
		Graph();
		~Graph();
		bool insert(const edge&);
		bool remove(const edge&);
		bool full_verify();
		bool verify_edge(int, int);
		bool remove_edge(int, int);
		void count_edge_vertex();
		void complete_graph();
		void print();
		void inicialize_weight();
		
		
};

void menu(int &opcao);

#ENDIF
		
	
	
	