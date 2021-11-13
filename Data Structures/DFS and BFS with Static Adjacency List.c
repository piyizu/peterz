#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* In this program, we use a static adjacency list to store a graph 
* and traverse it by both dfs and bfs. The program will print out
* the path of tracersal. You are required to input the number of 
* vertices and edges and the basic information of all edges.
* 
* This program uses two arrays to simulate a stack and a queue.
* The queue is 'cycling', for which it optimises the space of the 
* computer. Both implementations are interesting!
*/

#define MAX_V_NUM 1004
#define MAX_E_NUM 10004
#define MAX_QUEUE_SIZE 1024

int v[MAX_V_NUM], e[MAX_E_NUM], nxt[MAX_E_NUM], w[MAX_E_NUM];
int v_num, e_num, e_index = 1;

int visited[MAX_V_NUM], path[MAX_V_NUM], path_top = -1;
int queue[MAX_QUEUE_SIZE], front, rear;

void add_edge(int start, int end, int weight) {
	nxt[e_index] = v[start];
	v[start] = e_index;
	e[e_index] = end;
	w[e_index++] = weight;
}

void dfs(int v_index) {
	visited[v_index] = 1;
	path[++path_top] = v_index;
	for (int i = v[v_index]; i; i = nxt[i]) {
		if (!visited[e[i]])
			dfs(e[i]);
	}
}

void pushback(int v_index) {
	if (front == rear + 1) exit(EXIT_FAILURE); //queue full!
	queue[rear++] = v_index;
	if (rear == MAX_QUEUE_SIZE) rear = 0;
}

int emptyqueue() {
	return front == rear;
}

int popfront() {
	if (front == rear) exit(EXIT_FAILURE); //queue empty!
	int r = queue[front++];
	if (front == MAX_QUEUE_SIZE) front = 0;
	return r;
}

void bfs() {
	for (int i = 1; i <= v_num; ++i) {
		if (!visited[i]) {
			/////////////////
			pushback(i);
			visited[i] = 1; 
			// visited[v_index] is rendered true right after the vertex is pushed into the queue
			// in this way, each vertex will be in the queue only once
			while (!emptyqueue()) {
				int cur_v = popfront();
				path[++path_top] = cur_v;
				for (int j = v[cur_v]; j; j = nxt[j]) {
					if (!visited[e[j]]) {
						pushback(e[j]);
						visited[e[j]] = 1; //mark the vertex right after pushed
					}
				}
			}
			//above is non-recursion bfs for a connected component of a graph
		}
	}
}

int main() {
	scanf("%d%d", &v_num, &e_num);
	for (int i = 1; i <= e_num; ++i) {
		int start, end, weight;
		scanf("%d%d%d", &start, &end, &weight);
		add_edge(start, end, weight);
	}

	for (int i = 1; i <= v_num; ++i) {
		if (!visited[i])
			dfs(i);
	}

	for(int i = 0; i <= path_top; ++i)
		printf("%d ", path[i]);
	printf("\n");

	path_top = -1;
	memset(visited, 0, sizeof(visited));
	
	bfs();

	for (int i = 0; i <= path_top; ++i)
		printf("%d ", path[i]);

	return 0;
}