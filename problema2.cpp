// C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;
 
void CrearGrafoCiudad(vector<vector<int>>& G, int n);
void declararPuertos(vector<int>& p, int k, int n);
void CrearGrafoIslas(vector<vector<int>>& G, int m);
void imprimirGrafos(vector<vector<int>>& G, int n);

int minDistance(int dist[], bool sptSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the constructed distance
// array
void printSolution(int dist[], int V) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}
 

void dijkstra(vector<vector<int>>& graph, int src, int V) {
    int dist[V]; 
 
    bool sptSet[V]; 

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
    }
    }
 
    // print the constructed distance array
    printSolution(dist, V);
}

// driver's code
int main(int argc, char **argv) {
    /* Let us create the example graph discussed above */
	int n, m, k = 0;
	if(argc != 4 || atoi(argv[1]) <= atoi(argv[3])){
		cout << "Error. Debe ejecutarse como ./problema1 n m k. y n>k" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]); //numero de ciudades
	m = atoi(argv[2]); //numero de islas
	k = atoi(argv[3]); //numero de puertos
	srand(1000);
	int recibir = log2(k);
	int barcos = log2(m);

	//creacion del grafo

    srand(1000);

	vector<vector<int>> GrafoCiudad(n,vector<int>(n));

	vector<vector<int>> GrafoIslas(n,vector<int>(n));

    CrearGrafoCiudad(GrafoCiudad, n);

	CrearGrafoIslas(GrafoIslas, m);

    vector<int> puertos(k);

	vector<int> Aptos(recibir);

	declararPuertos(Aptos, recibir, m);

    declararPuertos(puertos, k, n);

    imprimirGrafos(GrafoCiudad, n);

	imprimirGrafos(GrafoIslas, m);

    dijkstra(GrafoCiudad, 0, n);

	dijkstra(GrafoIslas, 0, m);
 
    return 0;
    }

void CrearGrafoCiudad(vector<vector<int>>& G, int n) {
	bool connect = true;
	int *connection = new int[n];
	for(int i = 0; i<n; i++){
		connection[i] = 0;
	}
	while(connect == true){
		for(int i = 0; i<n ; i++){
			for(int j = 0; j<n;j++){
				int Aleatorio = rand()%2;
				if(i==j){
					G[i][j] = 0;
				}
				else if(Aleatorio == 1){
					int x = (rand()%20) + 1;
					G[i][j] = x;
					connection[j] = 1;
				}
				else if(Aleatorio == 0 and i==0 and j==n-1){
					int r = (rand()%(n-1)) + 1;
					int x = (rand()%20) + 1;
					G[0][r] = x;
					connection[r] = 1;
				}
				else{
					G[i][j] = 0;
				}
			}
		}
		connect = false;
		for(int j = 0; j < n; j++){
			if(connection[j] != 1){
				connect = true;
			}
		}
	}
}

void CrearGrafoIslas(vector<vector<int>>& G, int m){
	int cont = 0;
	bool connect = true;
	int *connection2 = new int[m];
	while(connect == true){
		cont = 0;
		for(int i = 0; i<m; i++){
			connection2[i] = 0;
		}
		for(int i = 0; i<m ; i++){
			for(int j = cont; j<m;j++){
				int Aleatorio = rand()%2;
				if(i==j){
					G[i][j] = 0;
					G[j][i] = 0;
				}
				else if(Aleatorio == 1){
					int x = (rand()%20) + 1;
					G[i][j] = x;
					G[j][i] = x;
					connection2[j] = 1;
					connection2[i] = 1;
				}
				else if(Aleatorio == 0 and j==m-1){
					cout<<"aqui"<<endl;
					int r = (rand()%(m-cont-1)) + 1 + cont;
					int x = (rand()%20) + 1;
					G[j][r] = x;
					G[r][j] = x;
					connection2[r] = 1;
					connection2[j] = 1;
				}
				else{
					G[i][j] = 0;
					G[j][i] = 0;
				}
			}
			cont=cont+1;
		}
		connect = false;
		
		for(int j = 0; j < m; j++){
			if(connection2[j] != 1){
				connect = true;
			}
		}
		for(int j = 0; j < m; j++){
			cout<<connection2[j]<<" ";
		}
		cout << endl;
		cout << endl;
	}
}

void declararPuertos(vector<int>& p, int k, int n) {
	for(int i = 0; i<k ; i++){
		int x = rand()%n;
		p[i] = x;
		}
}

void imprimirGrafos(vector<vector<int>>& G, int n) {
    for(int i = 0; i<n ; i++){
		for(int j = 0; j<n;j++){
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
/*
	int** GrafoIslas = new int*[m];
    for (int i = 0; i < m; i++){
        GrafoIslas[i] = new int[m];
    }

	for(int i = 0; i<m ; i++){
		for(int j = 0; j<=i;j++){
			int eleatorio = rand()%2;
			if(i==j){
				GrafoIslas[i][j] = 0;
				GrafoIslas[j][i] = 0;
			}
			else if(eleatorio == 1){
				int x = (rand()%20) + 1;
				GrafoIslas[i][j] = x;
				GrafoIslas[j][i] = x;
			}
			else{
				GrafoIslas[j][i] = 0;
				GrafoIslas[i][j] = 0;
			}
		}
	}

	cout<<"GrafoCiudad: "<< endl;
	for(int i = 0; i<m ; i++){
		for(int j = 0; j<m;j++){
			cout << GrafoCiudad[i][j] << " ";
		}
		cout << endl;
	}
*/