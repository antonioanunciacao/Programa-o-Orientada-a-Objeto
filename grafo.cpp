#include "graph.h"
using namespace std;

Graph::Graph() {
	FILE* file;
	file = fopen("grafo.txt", "r");
	fscanf(file, "%d", &num_vertex); // numero de vertico no grafo.txt
	
	// Criando a Matriz de Adjacencia:
	matrix_adjacency = new int*[num_vertex];
	for(int i = 0; i < num_vertex; i++) matrix_adjacency[i] = new int[num_vertex];
	for(int i = 0; i < num_vertex; i++)
		for(int j = 0; j < num_vertex; j++) matrix_adjacency[i][j] = 0;
	fclose(file);
	cout << "\n Seu Grafo foi Construido com Sucesso! \n:)" << endl;
}

Graph::~Graph() {
	for(int i = 0; i < num_vertex; i++) delete[] matrix_adjacency[i];
	delete[] matrix_adjacency;
	cout << "\n Destrutor do Grafo!" << endl;
}

bool Graph::insert() {
	FILE* file;
	file = fopen("grafo.txt", "r");
	int vert1, vert2, redundante = 0;
	bool existe;
	fscanf(file, "%d", &vert1);
	while(!feof(file)) {
		fscanf(file, "%d %d", &vert1, &vert2);
		if( existe == false) {
			matrix_adjacency[vert1][vert2] = 1;
			matrix_adjacency[vert2][vert1] = 1;
		}
		else redundante = 1;
	}
	fclose(file);
	if(redundante == 1) return false;
	else return true;
}

bool Graph::remove(int vertex_A, int vertex_B) {
	if(verify_edge(int vertex_A, int vertex_B)) == false) {
		cout << "Essa Aresta nao existe! :(" << endl;
		return false;
		}
	else {
		matrix_adjacency[vertex_A][vertex_B] = 0;
		matrix_adjacency[vertex_B][vertex_A] = 0;
		cout << "Aresta removida! :D" << endl;
		return true;
	}
}

bool Graph::full_verify(){
	int n = 0;
	for(int i = 0; i < num_vertex; i++)
		for(int j = 0; j < num_vertex; j++)
			if(matrix_adjacency[i][j] == 1) n++;
			else continue;
	n = n/2;
	// Atualizando o valor do numero de arestas:
	num_edges = n
	/*	Se um Grafo é completo todas os valores de 
		matrix_adjacency[i,j] com i!=j, sao 1.	*/
	if(n == (num_vertex*num_vertex) - n)/2)) return true;
	else return false;
}

void Graph::count_edge_vertex() {
	int n = 0;
	for(int i = 0; i < num_vertex; i++)
		for(int j = 0; j < num_vertex; j++)
			if(matrix_adjacency[i][j] == 1) n++;
			else continue;
	n = n/2;
	cout << "\n Arestas: " << n << endl;
	cout << "Vertices: " << num_vertex;
	// Atualizando o valor do numero de arestas:
	num_edges = n;
}

bool Graph::verify_edge(int vertex_A, int vertex_B) {
	// Verifica se o vertice faz parte da grafo:
	if(vertex_A >= num_vertex || vertex_B >= num_vertex) return false;
	// Verifica se a aresta ligando os dois vertices existe:
	if(matrix_adjacency[vertex_A][vertex_B] == 1) return true;
	// Aresta não existe:
	else return false;
}

void Graph::complete_graph() {
	if(full_verify() == false)
		for(int i = 0; i < num_vertex; i++)
			for(int j = 0; j < num_vertex; j++)
				if((matrix_adjacency[i][j] == 0) && (i != j)) matrix_adjacency[i][j] = 1;
	else continue;
}

// Codigo do DIJKSTRA retirado de https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
void Graph::Dijkstra(int src) {
	int minDistance(int dist[], bool sptSet[]) {
		int min = INT_MAX, min_index; 
		for (int v = 0; v < num_vertex; v++) 
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v; 
		return min_index;
	}
	
	int printSolution(int dist[], int n) {
		printf("Vertex   Distance from Source\n"); 
		for (int i = 0; i < V; i++) 
			printf("%d tt %d\n", i, dist[i]); 
	}
	
	int dist[num_vertex];
	inicialize_weight();
	
	bool sptSet[num_vertex];
	int parent[num_vertex];
	
	for(int i = 0; i < num_vertex; i++) {
		parent[0] = -1;
		dist[i] = INT_MAX; // parametro da biblioteca <climits>
		stpSet[i] = false;
	}
	
	dist[src] = 0;
	for(int count = 0; count < num_vertex - 1; count++) {
		int u = minDistance(dist, sptSet);
		sptSet[u] = true;
		for(int v = 0; v < num_vertex; v++)
			if(!sptSet[v] && matrix_weights[u][v] && dist[u] + matrix_weights[u][v] < dist[v]) {
				parent[v] = u;
			dist[v] = dist[u] + matrix_weights[u][v];
			}
	}
	printSolution(dist, num_vertex, parent);
	cout << endl;
	for(int i = 0; i < num_vertex; i++) delete[] matrix_weights[i];
	delete[] matrix_weights;
}
		
void Graph::print() {
	count << "\n  ";
	for(int i = 0; i < num_vertex; i++) cout << " " << i << " ";
	cout << endl;
	for(int i = 0; i < num_vertex; i++) {
		cout << " " << i << " ";
		for(int j = 0; j < num_vertex; j++) cout << "| " << matrix_adjacency[i][j];
		cout << endl;
	}
}

void Graph::inicialize_weight() {
	matrix_weights = new int*[num_vertex];
	for(int i = 0; i < num_vertex; i++) matrix_weights[i] = new int[num_vertex];
	for(int i = 0; i < num_vertex; i++)
		for(int j = 0; j < num_vertex; j++) matrix_weights[i][j] = 0;
	
	int weight;
	for(int i = 0; i < num_vertex; i++)
		for(int j = 0; j < num_vertex; j++)
			if(matrix_weights[i][j] == 0)
				if((i!=j) && (matrix_adjacency[i][j] == 1)) {
					cout << "Entre com o peso para a Aresta " << i << " e " << j << endl;
					cin >> weight;
					matrix_weights[i][j] = weight;
					matrix_weights[j][i] = weight;
				}
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	