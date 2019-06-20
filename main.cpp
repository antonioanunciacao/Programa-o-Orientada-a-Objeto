#include <iostream>	//Biblioteca Padrão
#include "grafo.cpp"
using namespace std;

int main() {
	Graph grafo;
	bool operacao;
	int vertex_A, vertex_B, opcao;
	menu(opcao);
	while( opcao != 8 ) {
		operacao = false;
		
		if( opcao == 1 ) {
			operacao = grafo.insert();
			grafo.print();
		}
		else if( opcao == 2 ) {
			cout << "\n Entre com os vertices da Aresta que deseja remover: ";
			while( operacao == false) {
				cin >> vertex_A >> vertex_B;
				if(grafo.verify_edge(vertex_A, vertex_B) == true) operacao = grafo.remove(vertex_A, vertex_B);
				else cout << "\nAresta nao existe, entre com uma aresta existente!\n";
			}
			cout << "\nAresta removida!";
		}
		else if( opcao == 3 ) {
			cout << "Entre com os vertices da aresta desejada: ";
			cin >> vertex_A >> vertex_B;
			if(grafo.verify_edge(vertex_A, vertex_B) == false)
				cout << "\nAresta inexistente!\n";
			else cout << "\nParabens, essa aresta existe!\n";
		}
		else if( opcao == 4 ) {
			grafo.count_edge_vertex();
		}
		else if( opcao == 5 ) {
			if( grafo.full_verify() == false) {
				cout << "\nGrafo incompleto!";
				cout << "\nDeseja completa-lo? \n(1) - Sim \n(2) - Nao\n";
				while( opcao != 1 || opcao != 2 ) {
					if( opcao == 1 ) grafo.complete_graph();
					else if( opcao == 2 ) continue;
					else cout << "\nOpcao invalida!";
				}
			}
			else cout << "\nGrafo completo!";
		}
		else if( opcao == 6 ) {
			grafo.complete_graph();
			grafo.print();
		}
		else {
			//grafo.Dijkstra(0);
		}
		menu(opcao);
	}
	return 0;
};