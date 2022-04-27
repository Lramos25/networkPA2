#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>


using namespace std;

#define INF 1073741824

int V, src, cost[100][100];
int dist[100];
bool visited[100] = {0}; //start with all nodes set to "not visited"
int parent[100];

// Put each distance from each source node to INF - the source node didstance to itself is 0
void init() {
	for (int i = 0; i < V; i++) {
		parent[i] = i;
		dist[i] = INF;
	}
	dist[src] = 0;
}


//Figure out which node is the next closest node
int getNearest() {
	int minValue = INF;
	int minNode = 0;
	for (int i = 0; i < V; i++) {
		if (!visited[i] && dist[i] < minValue) {
			minValue = dist[i];
			minNode = i;
		}
	}
	return minNode;
}


// use Dijkstras algo 
// start at source node 
// get distance to each adjecent node
// update distance table 
// move to next nearest node that has not been visited and repeat

void dijkstra() {
	for (int i = 0; i < V; i++) {
		int nearest = getNearest();
		visited[nearest] = true;

		for (int adj = 0; adj < V; adj++) {
			if (cost[nearest][adj] != INF && dist[adj] > dist[nearest] + cost[nearest][adj]) {
				dist[adj] = dist[nearest] + cost[nearest][adj];
				parent[adj] = nearest;
			}
		}
	}
}


//print final results of forwarding table
void display() {
	cout << "Node:\t\t\tCost: \t\t\tPath:" << endl;

	for (int i = 0; i < V; i++) {
		cout << i << "\t\t\t" << dist[i] << "\t\t\t" << " ";

		cout << i << " ";
		int parnode = parent[i];

		while (parnode != src) {
			cout << "<--" << parnode << " ";
			parnode = parent[parnode];
		}
		cout << endl; 
	}
}


int main(void) {
	// get the time start processing
	auto start = chrono::steady_clock::now();

	cout << "Number of Vertices: ";
	cin >> V;

	cout << "Cost matrix " << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cin >> cost[i][j];
		}
	}

	cout << "Source Node: ";
	cin >> src;
	init();
	dijkstra();
	display();

	// get the time after processing
	auto end = chrono::steady_clock::now();

	// compute the difference
	cout << "\nExecution time: " << chrono::duration <double, milli>(end - start).count() << "ms" << endl;
	return 0;

}