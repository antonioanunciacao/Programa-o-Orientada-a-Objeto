/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS
ENGENHARIA DE SISTEMAS

IMPLEMENTAÇÃO DE CLASSE PARA OPERAR GRAFOS
DISCIPLINA:	PROGRAMAÇÃO ORIENTADA A OBJETOS
PROFESSORA:	Raquel Mini
AUTORES:	Antonio Carlos da Anunciação	2018019443 
			Warley França Abreu				2018438098
*/

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

// Estrutura para representar aresta, composto de dois vertices e um peso.
typedef struct Edge	{
	int vertex_A, vertex_B; // Define os valores dos vertices conectados a uma aresta.
	int weight; // Define o peso de uma aresta.
} Edge;

// Estrutra da nossa classe principal
class Graph	{
	private:
		int num_vertex, num_edge;	// Atributos Privados, numero de vertices e numero de arestas
		int** adjacency_matrix;		// Atributo Privado, armazena os pesos das arestas

        bool BFS(const int&, bool[]) const;									// Metodo Privado, auxiliar das funções de buscas
        void permutation(const Graph&, int*, int*, int&, const int&) const; // Metodo Privado, auxiliar das funções de buscas
    
	public:
	    Graph(int);     // Construtor da classe
        ~Graph();		// Destrutor da classe

        int number_of_edge() const;					// Metodo retorna o numero de arestas
        int number_of_vertex() const;				// Metodo retorna o numero de vertices

        int weight(int, int) const;					// Metodo retorna o peso de uma aresta
        bool insert(const Edge&);					// Metodo insere uma aresta
        bool remove(const Edge&);					// Remove uma aresta
        bool verify_edge(const Edge&) const;		// Metodo verifica se uma aresta é valida
        bool verify_graph() const;					// Metodo verifica se um grafo esta completo
		void complete_graph();						// Metodo completar um grafo
        Graph fill_graph(const int&)  const;		// Metodo auxiliar para completer grafo dentro do metodo do Caixeiro Viajante
        void BFS(const int&) const;					// Metodo busca na largura
        void DFS(const int&) const;					// Metodo busca na profundidade
		void print() const;							// Metodo imprime matriz de adjcencia na tela
		void save();								// Metodo salva matriz de adjacencia
        int number_of_component() const;			// Metodo retorna o numero de componentes de um grafo
        void Dijkstra(int, int, int**, int&, int&);	// Metodo calcula a menor distancia entre dois vertices
        Graph TSM(const int&, const int&) const;	// Metodo auxilar para o Caixeiro Viajante
        Graph MST() const; 							// Metodo auxilar para o Caixeiro Viajante
};

void menu(int&); //Função para executar as operações do nosso programa.

#endif // GRAPH_H
