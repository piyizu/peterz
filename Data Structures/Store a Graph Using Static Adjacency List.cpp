#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstring>

/*
* This program shows a way to store a graph. The basic idea is the adjacency list.
* We do not implement the list as we did for simple linked lists.
* We use static data structures (here they are arrays and global variables) to do that.
* Those static objects act like linked list.
*/

const int MAX_VERTEX_NUM = 1e2 + 1, MAX_EDGE_NUM = 1e3 + 1, INF = 0x3f3f3f3f;

int v[MAX_VERTEX_NUM], e[MAX_EDGE_NUM], nxt[MAX_EDGE_NUM], w[MAX_EDGE_NUM];
int n_vertex, n_edge, eindex = 1; //index started from 1 would be easy.

//data explanation:
//v[vertex_index]:index of the last edge started from this vertex
//e[edge_index]:index of the vertex the edge connects to
//nxt[edge_index]:index of the next edge with the same starting vertex
//w[edge_index]:weight of the edge

void add_edge(int start, int end, int weight) {
	nxt[eindex] = v[start];
	v[start] = eindex;
	w[eindex] = weight;
	e[eindex++] = end; // ++ is necessary.
}

void print_graph() {
	printf("(Vertex) [Edge]{weight}(To)\n");
	for (int i = 1; i <= n_vertex; ++i) {
		printf("(%d) ", i);
		for (int j = v[i]; j; j = nxt[j]) { //visit all edges starting from the vertex
			printf("[%d]{%d}(%d) ", j, w[j],e[j]);
		}
		printf("\n");
	}
}

int main() {
	printf("The number of vertices:");
	while (scanf("%d", &n_vertex) != 1) printf("Retry:");
	printf("The number of edges:");
	while( scanf("%d", &n_edge) != 1) printf("Retry:");
	for (int i = 0; i < n_edge; ++i) {
		int start, end, weight;
		printf("Starting Vertex (Blankspace) Ending Vertex (Blankspace) Weight:");
		while (scanf("%d%d%d", &start, &end, &weight) != 3) printf("Retry:");
		add_edge(start, end, weight);
	}
	print_graph();
	return 0;
}