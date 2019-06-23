#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, char *argv[]) {
	ifstream entrada;
    streambuf *oldbuff = cin.rdbuf();
	
    int *path, vnum, lenght, i, j, vertex_A, vertex_B, num_vertex, num_edge;
	int opcao = 0;
	bool operacao;
		
	//__________________________________________________________________________________
	//CARREGANDO OS DADOS DO ARQUIVO PARA A MEMORIA:
    if(argc > 1) {
		entrada.open(argv[1]);
		if(!entrada.good()) {
			cout << "O arquivo \"" << argv[1] << "\" nao existe!\n";
            return 0;
        }
        cin.rdbuf(entrada.rdbuf());
	}
	else {
		cout << "Nenhum arquivo foi passado!\n";
        return 0;
    }

    do {
        cin >> num_vertex >> num_edge;
        if(num_vertex < 1) {
            cout << "Numero de vertices invalido\n";
            cout << num_vertex << " " << num_edge;
            return 0;
        }
        else if(num_edge < 0) {
            cout << "Numero de arestas invalido\n";
            cout << num_vertex << " " << num_edge;
            return 0;
        }

    } while(num_vertex < 1 || num_edge < 0);
	
	Graph *grafo = new Graph(num_vertex);
    Edge edge;
	for(i = 0; i < num_edge; i++) {
		cin >> edge.vertex_A >> edge.vertex_B >> edge.weight;
		grafo->insert(edge);
	}
	
	if(argc > 1) {
        entrada.close();
        cin.rdbuf(oldbuff);
    }
	
	//__________________________________________________________________________________
	//FIM DO CARREGAMENTO
	
	//__________________________________________________________________________________
	//LOOP DO MENU INICIAL
	
	while( opcao != 99 ) {
		operacao = false;
		
		if( opcao == 0 ) {
			system("cls");
		}
		
		else if( opcao == 1) {
			grafo->print();
		}
		
		else if( opcao == 2 ) {
			Edge aux_edge;
			cout << "\n Entre com os vertices e peso da aresta que deseja adicionar: ";
			while( operacao == false ) {
				cin >> aux_edge.vertex_A >> aux_edge.vertex_B >> aux_edge.weight;
				if(grafo->verify_edge(edge) == true) {
					operacao = grafo->insert(aux_edge);
				}
				else cout << "\nAresta nao existe, entre com uma aresta existente!\n";
			}
			cout << "\nPeso da aresta atualizado!\n";
		}		
		
		else if( opcao == 3 ) {
			cout << "\n Entre com a aresta que deseja remover: ";
			while( operacao == false ) {
				cin >> edge.vertex_A >> edge.vertex_B;
				if(grafo->verify_edge(edge) == true) operacao = grafo->remove(edge);
				else cout << "\nAresta nao existe, entre com uma aresta existente!\n";
			}
			cout << "\nAresta removida!";
		}
		
		else if( opcao == 4 ) {
			cout << "Entre com os vertices da aresta desejada: ";
			cin >> vertex_A >> vertex_B;
			if(grafo->weight(vertex_A, vertex_B) <= 0) cout << "\nAresta inexistente!\n";
			else {
				cout << "\nParabens, essa aresta existe!" << endl;
				cout << "Peso da aresta: " << grafo->weight(vertex_A, vertex_B) << endl;
			}
			
		}
		
		else if( opcao == 5 ) {
			cout << "\nO grafo contem:\n" << "Arestas: " << grafo->number_of_edge()
			<< ", Vertices: " << grafo->number_of_vertex();
			cout << endl;
		}

		else if( opcao == 6 ) {
			if( grafo->verify_graph() == false) {
				cout << "\nDeseja completa-lo? \n(1) - Sim \n(2) - Nao\n";
				while( opcao != 1 || opcao != 2 ) {
					cin >> opcao;
					if( opcao == 1 ) {
						grafo->complete_graph();
						break;
					}
					else if( opcao == 2 ) break;
					else cout << "\nOpcao invalida!";
				}
			}
		}
		
		else if( opcao == 7 ) {
			int aux_vertex = grafo->number_of_vertex();
			if((((aux_vertex*aux_vertex) - aux_vertex)/2) == grafo->number_of_edge()) cout << "\nEste grafo ja esta completo!\n";
			else grafo->complete_graph();
		}
		
		else if( opcao == 8 ) {
			int vertex;
			cout << "\nEntre com o valor do vertice: ";
			cin >> vertex;
			grafo->BFS(vertex);
		}
		
		else if( opcao == 9 ) {
			int vertex;
			cout << "\nEntre com o valor do vertice: ";
			cin >> vertex;
			grafo->DFS(vertex);
		}
		
		else if( opcao == 10 ) {
			ofstream dijkstra;
			dijkstra.open("dijkstra.txt", ios::out);
			int vertex_1, vertex_2;
			cout << "\nEntre com o valor os valores dos vertices: ";
			cin >> vertex_1 >> vertex_2;
			grafo->Dijkstra(vertex_1, vertex_2, &path, vnum, lenght);
			for(i = 0; i < vnum; i++) {
				cout << path[i] << " ";
				dijkstra << path[i] << " ";
			}
			cout << "- Distancia: " << lenght << endl;
			dijkstra << "- Distancia: " << lenght << endl;
			dijkstra.close();			
		}
		
		else if( opcao == 11 ) {
			grafo->MST().BFS(1);
		}

		else if( opcao == 12 ) {
			grafo->TSM(1, 30).DFS(1);
		}

		else if( opcao == 13 ) {
			cout << grafo->number_of_component() << endl;
		}
		
		else {
			cout << "\nOxe! Entre com um numero dentre os das opcoes do Menu!\n"; 
		}
		menu(opcao);
	}
	
	grafo->save();
	
	//__________________________________________________________________________________
	//FIM DO PROGRAMA
	
    delete grafo;
    return 0;
}
