#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Minimum Cost Spanning Tree with Prim, 
* Close_edge Array and Static Adjacency List
* It will print out the edge indexes of the MST.
* You can find the tree according to your typing.
* Note: the index of edges is counted from 1 as you input
*/

#define MAX_V_NUM 1004
#define MAX_E_NUM 10004
#define MAX_STACK_SIZE 1024
#define INF 0x3f3f3f3f

int v[MAX_V_NUM], e[MAX_E_NUM], nxt[MAX_E_NUM], w[MAX_E_NUM];
int v_num, e_num, e_index = 1;
int close_edge[MAX_V_NUM], solution_stack[MAX_STACK_SIZE], solution_top = -1, total_weight = 0;

//close_edge[v_index]:e_index, indicates the shortest edge connnects S and v_index.
// if e_index is 0, v_index is already in S.
// if e_index is -1, v_index has no direct edge connected to S

void add_edge(int start, int end, int weight) {
	nxt[e_index] = v[start];
	v[start] = e_index;
	e[e_index] = end;
	w[e_index++] = weight;
}

int minimum(int *close_edge) {
	int v_index;
	for (v_index = 1; v_index <= v_num && close_edge[v_index] <= 0 ; ++v_index); 
	//find the first valid edge in close_edge and return the ending vertex index
	if (v_index == v_num + 1) return 0; //no valid edge, the graph may be disconnected
	for (int i = v_index + 1; i <= v_num; ++i) {
		if (close_edge[i] >= 1 && w[close_edge[i]] < w[close_edge[v_index]])
			v_index = i;
	}
	return v_index;
}

int main() {
	scanf("%d%d", &v_num, &e_num);
	for (int i = 1; i <= e_num; ++i) {
		int start, end, weight;
		scanf("%d%d%d", &start, &end, &weight);
		add_edge(start, end, weight);
	}

	memset(close_edge, 0xff, sizeof(close_edge));

	close_edge[1] = 0; //let vertex 1 in S
	int cur = 1; // current vertex is 1 and we will use it to update close_edge
	for (int i = 1; cur && i <= v_num - 1; ++i) {
		for (int j = v[cur]; j; j = nxt[j]) { //refresh close_edge
			if (close_edge[e[j]] < 0 || (close_edge[e[j]] >= 1 && w[j] < w[close_edge[e[j]]]) )
				close_edge[e[j]] = j;
		}
		cur = minimum(close_edge);
		if (cur == 0) continue; //cannot find valid minimal edge
		total_weight += w[close_edge[cur]]; 
		//add one vertex more, and you can get one more edge of the tree
		solution_stack[++solution_top] = close_edge[cur]; //record the tree.
		close_edge[cur] = 0;
	}

	for (int i = 0; i <= solution_top; ++i)
		printf("%d ", solution_stack[i]);
	printf("TOTAL WEIGHT:%d", total_weight);
	return 0;
}