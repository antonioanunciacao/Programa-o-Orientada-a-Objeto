/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS
ENGENHARIA DE SISTEMAS

IMPLEMENTAÇÃO DE CLASSE PARA OPERAR GRAFOS
DISCIPLINA:	PROGRAMAÇÃO ORIENTADA A OBJETOS
PROFESSORA:	Raquel Mini
AUTORES:	Antonio Carlos da Anunciação
			Warley França Abreu
*/


#include "Graph.h"
using namespace std;

void menu(int &opcao) {
	cout << "\n *******************************************************\n";
	cout << " * Escolha o que voce quer fazer:                       *\n";
	cout << " * 01 - Imprime Grafo                                   *\n";
	cout << " * 02 - Adicionar Aresta                                *\n";
	cout << " * 03 - Remover Aresta                                  *\n";
	cout << " * 04 - Busca Aresta                                    *\n";
	cout << " * 05 - Verificar vertices e Arestas                    *\n";
	cout << " * 06 - Verificar Grafo                                 *\n";
	cout << " * 07 - Completar Grafo                                 *\n";
	cout << " * 08 - BFS: Busca em Largura                           *\n";
	cout << " * 09 - DFS: Busca em Profundidade                      *\n";
	cout << " * 10 - Dijkstra, Menor distancia entre dois vertices   *\n";
	cout << " * 11 - Arvore Geradora Minima                          *\n";
	cout << " * 12 - Caixeiro viajante                               *\n";
	cout << " * 13 - Numero de componentes                           *\n";
	cout << " * 50 - Salvar Grafo atual                              *\n";
	cout << " * 99 - Salvar dados e sair                             *\n";
	cout << " *******************************************************\n";
	cout << " Entre com sua opcao: ";
	cin >> opcao;
};

Graph::Graph(int num_vertex = 0) {
    this->num_vertex = num_vertex;
    this->num_edge = 0;

    adjacency_matrix = new int*[num_vertex];
    for(int i = 0; i < num_vertex; i++) adjacency_matrix[i] = new int[num_vertex]();
}

Graph::~Graph()	{
	for (int i = 0; i < num_vertex; ++i) delete[] adjacency_matrix[i];
    delete[] adjacency_matrix;
}

int Graph::number_of_edge() const {
    return num_edge;
}

int Graph::number_of_vertex() const	{
    return num_vertex;
}

int Graph::weight(int vertex_a, int vertex_b) const	{
	if(vertex_a > num_vertex || vertex_a < 1 || vertex_b > num_vertex || vertex_b < 1) return -1;
	else return adjacency_matrix[vertex_a-1][vertex_b-1];
}

bool Graph::insert(const Edge& edge) {
	if(verify_edge(edge) == false) {
		cout << "\nAresta nao existente!\n";
		return false;
	}
	else if(adjacency_matrix[edge.vertex_A-1][edge.vertex_B-1] != 0){
		adjacency_matrix[edge.vertex_A-1][edge.vertex_B-1] = edge.weight;
		adjacency_matrix[edge.vertex_B-1][edge.vertex_A-1] = edge.weight;
		return true;
	}
	else {
		num_edge++;
		adjacency_matrix[edge.vertex_A-1][edge.vertex_B-1] = edge.weight;
		adjacency_matrix[edge.vertex_B-1][edge.vertex_A-1] = edge.weight;
		return true;
	}
}

bool Graph::remove(const Edge& edge) {
	if(verify_edge(edge) == false)	{
		cout << "\nAresta nao existe!\n";
		return false;
	}

	else {
		num_edge--;
		adjacency_matrix[edge.vertex_A-1][edge.vertex_B-1] = 0;
		adjacency_matrix[edge.vertex_B-1][edge.vertex_A-1] = 0;
		cout << "\nAresta removida com sucesso!\n";
		return true;
	}
}

bool Graph::verify_edge(const Edge& edge) const {
    if(edge.vertex_A < 1 || edge.vertex_B < 1 || edge.vertex_A > num_vertex || edge.vertex_B > num_vertex) return false;
	else return true;
}

bool Graph::verify_graph() const {
	if((number_of_edge() < ((number_of_vertex()*number_of_vertex()) - number_of_vertex())/2))	{
		cout << "\nGrafo incompleto!\n";
		return false;
	}
	else {
		cout << "\nGrafo completo!\n";
		return true;
	}
}

void Graph::complete_graph() {
	Edge aux_edge;
	for(int i = 0; i < num_vertex; i++){
		aux_edge.vertex_A = 1 + i;
		for(int j = 0; j < num_vertex; j++)
			if((adjacency_matrix[i][j] == 0) && (i != j)) {
				aux_edge.vertex_B = 1 + j;
				aux_edge.weight = 1;
				insert(aux_edge);
			}
	}
}
			
Graph Graph::fill_graph(const int& weight = 1) const {
	Graph grafo(num_vertex);
	Edge edge;

    for(int i = 0; i < num_vertex; i++) {
		edge.vertex_A = i+1;
        for(int j = 0; j < num_vertex; j++) {
            edge.vertex_B = j+1;
            edge.weight = adjacency_matrix[i][j];
			if(i != j && edge.weight == 0) edge.weight = weight;
			else grafo.insert(edge);
        }
    }
    return grafo;
}

void Graph::print() const {
	for(int i = 1; i <= num_vertex; i++) {
		for(int j = 1; j <= num_vertex; j++) cout << weight(i, j) << " ";
		cout << endl;
    }
}

void Graph::save() {
	ofstream matrix;
	matrix.open("adjacency_matrix.txt", ios::out);
	for(int i = 1; i <= num_vertex; i++) {
		for(int j = 1; j <= num_vertex; j++) matrix << weight(i, j) << " ";
		matrix << endl;
    }
	matrix.close();
}

void Graph::BFS(const int& vertex) const {
    if(vertex < 1 || vertex > num_vertex) {
		cout << "\nVertice inicial invalido!\n";
		return;
	}
    queue <int> q; // Cria uma fila
	bool* visited = new bool[num_vertex](); // Indica as posicoes ja visitadas
    q.push(vertex-1); // Insere o vertice inicial na fila
    visited[vertex-1] = true; // Indica que o vertice inicial foi visitado

    int a, i; // Elemento atual a ser lido
	ofstream bfs;
	
	bfs.open("BFS.txt", ios::out);
	
    // Enquanto a fila nao estiver vazia, execute o codigo
    do {
		// Remove um elemento da fila
        a = q.front();
        q.pop();

        cout	<< a+1 << " ";
		bfs		<< a+1 << " ";
		
		for(i = 0; i < num_vertex; i++) {
            // Verifica se o vertice ja foi visitado e se tem peso entre os vertices
            if(visited[i] == false && adjacency_matrix[a][i] != 0) {
                // Insere o vertice na fila
                q.push(i);
				// Indica que o verticefoi visitado
                visited[i] = true;
			}
        }
	} while(!q.empty());

    cout << endl;
	bfs << endl;
	
	bfs.close();
	
    delete[] visited;
}

void Graph::DFS(const int& vertex) const {
	if(vertex < 1 || vertex > num_vertex)  return;

    stack <int> s; // Cria uma pilha
	bool* visited = new bool[num_vertex](); // Indica as posicoes ja visitadas
	s.push(vertex-1); // Insere o vertice inicial na pilha
	visited[vertex-1] = true; // Indica que o vertice inicial foi visitado

    int a, i; // Elemento atual a ser lido
	ofstream dfs;
	
	dfs.open("DFS.txt", ios::out);
	
    // Enquanto a pilha nao estiver vazia, execute o codigo
    do {
		// Remove um elemento da pilha
        a = s.top();
        s.pop();

        cout << a+1 << " ";
		dfs << a+1 << " ";

        for(i = 0; i < num_vertex; i++) {
            // Verifica se o vertice ja foi visitado e se tem peso entre os vertices
            if(visited[i] == false && adjacency_matrix[a][i] != 0) {
                // Insere o vertice na pilha
                s.push(i);
				// Indica que o verticefoi visitado
                visited[i] = true;
			}
        }
	} while(!s.empty());

    cout << endl;
	dfs << endl;
	dfs.close();
    delete[] visited;
}

bool Graph::BFS(const int& vertex, bool visited[]) const {
	queue <int> q; // Cria uma fila
	q.push(vertex); // Insere o vertice inicial na fila
	visited[vertex] = true; // Indica que o vertice inicial foi visitado
	bool con = false; // Indica se houve conexao de componentes
	
	int a, i; // Elemento atual a ser lido
	
    // Enquanto a fila nao estiver vazia, execute o codigo
    do {
		// Remove um elemento da fila
        a = q.front();
        q.pop();

        for(i = 0; i < num_vertex; i++) {
            // Verifica se o vertice ja foi visitado e se tem peso entre os vertices
            if(visited[i] == false && adjacency_matrix[a][i] != 0) {
                // Insere o vertice na fila
                q.push(i);
				// Indica que o verticefoi visitado
                visited[i] = true;
				// Indica que houve conexao de componentes
                con = true;
            }
        }
    } while(!q.empty());
    return con; // Indica se houve conexao de componentes
}

int Graph::number_of_component() const {
    // Numero de componentes do grafo
    int n = 0;

    // Indica as posicoes ja visitadas
    bool* visited = new bool[num_vertex]();

    // Verifica em todos vertices suas conexoes, sem repetir conexoes ja feitas
    for(int i = 0; i < num_vertex; i++) 
        if(!visited[i] && BFS(i, visited)) n++;
    
    delete[] visited;
    // Mostra o numero de componentes conectados
    return n;
}

// Algoritmo de Dijkstra
void Graph::Dijkstra(int vertex_a, int vertex_b, int** path, int& vnum, int& lenght) {

    // Verifica se existe os vertices
    if(vertex_a < 1 || vertex_b < 1 || vertex_a > num_vertex || vertex_b > num_vertex)    return;

    // Distancia da fonte para posicao
    int* d = new int[num_vertex]();

    // Vertice anterior
    int* prev = new int[num_vertex]();

    // Indica as posicoes ja visitadas
    bool* visited = new bool[num_vertex]();

    // Numero de vertices visitados
    int numvisited = 0;

    // Auxiliar de minima distancia
    int mindist, minpos;
    int i;

    // Inicializacao das variaveis de controle
    for(i = 0; i < num_vertex; i++) {
        d[i] = numeric_limits<int>::max();
        prev[i] = -1;
    }
    // Distancia do inicio para o inicio
    d[vertex_a-1] = 0;

    while(numvisited != num_vertex) {
        // Reinicia a minima distance
        mindist = numeric_limits<int>::max();

        // Descobre o vertice de distancia minima da atual
        for(i = 0; i < num_vertex; i++) {
            if(!visited[i]) {
                if(mindist >= d[i]) {
                    mindist = d[i];
                    minpos = i;
                }
            }
        }

        // Indica que a posicao foi visitada
        visited[minpos] = true;
        numvisited++;

        // Atualiza a distancia dos vizinhos do vertice atual
        for(i = 0; i < num_vertex; i++) {
            if(!visited[i] && adjacency_matrix[minpos][i] != 0) {
				mindist = d[minpos] + adjacency_matrix[minpos][i];
                if(mindist < d[i]) {
                    d[i] = mindist;
                    prev[i] = minpos;
                }
            }
        }
    }

    // Inicializa as variaveis de saida
    *path = new int[num_vertex];

    // Comeca do fim
    minpos = vertex_b-1;

    // Inicializa a distancia como 0
    lenght = d[minpos];

    // Numero de vertices inicialmente como 0
    vnum = 0;

    // Verifica qual a distancia
    for(vnum = 0; minpos != -1; vnum++) {
        minpos = prev[minpos];
    }
    // Comeca do fim
    minpos = vertex_b-1;
    for(i = 0; i < vnum; i++) {
        (*path)[vnum-i-1] = minpos+1;
        minpos = prev[minpos];
    }

    delete[] d;
    delete[] prev;
    delete[] visited;
}

// Problema do caixeiro viajante
Graph Graph::TSM(const int& start, const int& weight) const {
    // Grafo de solucao do problema
    Graph grafo (num_vertex);

    // Posicao inicial invalida
    if(start < 1 || start > num_vertex ) return grafo;

    // Grafo auxiliar
    Graph aux_grafo = fill_graph(weight);

    // Maior distancia inicialmente e infinita
    int ldistance = numeric_limits<int>::max();

    // Vetor auxiliar de caminho
    int* pvector = new int[num_vertex+1];

    // Vetor de menor caminho
    int* lpath = new int[num_vertex+1];

    Edge edge;
    int i;

    // Primeira e ultima posicao e a cidade inicial
    pvector[0] = start;
    lpath[0] = start;
    pvector[num_vertex] = start;
    lpath[num_vertex] = start;

    // Armazena o caminho inicial
    for(i = 1; i < num_vertex; i++) {
        if(i >= start) pvector[i] = i+1;
        else pvector[i] = i;
    }
    // Faz a permutacao do vetor pvector
    permutation(aux_grafo, pvector, lpath, ldistance, num_vertex);

    // Armazena o caminho e distancia no grafo de saida
    for(i = 0; i < num_vertex; i++) {
        edge.vertex_A = lpath[i];
        edge.vertex_B = lpath[i+1];
        edge.weight = adjacency_matrix[edge.vertex_A-1][edge.vertex_B-1];
        grafo.insert(edge);
    }
    delete[] pvector;
    delete[] lpath;
    return grafo;
}

void Graph::permutation(const Graph& grafo, int* pvector, int* lpath, int& ldistance, const int& m) const {
    int i;

    if(m == 2) {
        int distance = 0;
        // Armazena as distancias entre as cidades no caminho dado pelo vetor
        for(i = 0; i < num_vertex; i++) distance += grafo.weight(pvector[i], pvector[i+1]);

        // Se a distancia calculada for menor que a armazenada, renova o valor
        if(distance < ldistance) {
            for(i = 1; i < num_vertex; i++) lpath[i] = pvector[i];
            ldistance = distance;
        }
    }
    else {
		for (i = 1; i < m; i++) {
			permutation(grafo, pvector, lpath, ldistance, m-1);
			if (m % 2 == 1) swap(pvector[1], pvector[m-1]);
			else swap(pvector[i], pvector[m-1]);
        }
    }
}

// Arvore Geradora Minima pelo algoritmo de Prim
Graph Graph::MST() const {
    Graph grafo (num_vertex);
    bool* visited = new bool[num_vertex](); // Indica as posicoes ja visitadas
    visited[0] = true; // Primeiro vertice ja visitado

    // Vertice aresta com menor peso verificado
    Edge loweredge;
    int i, j, k;
    // Checa todos vertices
    for (i = 0; i < num_vertex; i++)
    {
        // Reseta o peso
        loweredge.weight = numeric_limits<int>::max();
        for (j = 0; j < num_vertex; j++) {
            if(visited[j]) {
                // Verifica os pesos dos vertices conectados
                for (k = 0; k < num_vertex; k++) {
                    if(!visited[k]) {
                        // Se o peso entre dados vertices for menor que o armazenado, troca por este valor
                        int weight = adjacency_matrix[j][k];
                        if(weight != 0 && weight < loweredge.weight) {
                                loweredge.vertex_A = j+1;
                                loweredge.vertex_B = k+1;
                                loweredge.weight = weight;
                        }
                    }
                }

            }
        }
        // Se encontrou um peso diferente de 0 entre os vertices
        if(loweredge.weight != numeric_limits<int>::max()) {
            visited[loweredge.vertex_B-1] = true; // Indica que o vertice ja foi visitado          
            grafo.insert(loweredge); // Insere o vertice na arvore geradora minima
        }
    }
    delete[] visited;
    return grafo;
}
