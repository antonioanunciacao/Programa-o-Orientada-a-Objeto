#IFNDEF GRAFO_H
#DEFINE GRAFO_H

#include <iostream>	//Biblioteca Padrão
#include <fstream>	//Biblioteca Entrada e saida de arquivos
#include <string>	//Biblioteca de strings
#include <cstdio>

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
		void Dijkstra(int src);		
};

void menu(int &opcao) {
	cout << " ******************************************************\n";
	cout << " * Escolha o que voce quer fazer:                     *\n";
	cout << " * 1 - Inserir Aresta 								   *\n";
	cout << " * 2 - Remover Aresta                                 *\n";
	cout << " * 3 - Busca Aresta                                   *\n";
	cout << " * 4 - Verificar vertices e Arestas                   *\n";
	cout << " * 5 - Verificar Grafo                                *\n";
	cout << " * 6 - Completar Grafo                                *\n";
	cout << " * 7 - Menor Caminho                                  *\n";
	cout << " * 8 - Sair                                           *\n";
	cout << " ******************************************************\n";
	cout << " Entre com sua opcao: ";
	cin >> opcao;
};


#ENDIF
		
	
	
	