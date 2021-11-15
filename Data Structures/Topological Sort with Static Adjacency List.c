//#include <stdio.h>

/*
  Topological sort, as is named, is a kind of sort, telling if a graph is a Directed Acyclic Graph.
*/

#define V_MAX 1004
#define E_MAX 10004
#define STACK_MAX 1024

int vertex[V_MAX], edge[E_MAX], next[E_MAX], weight[E_MAX];
int v_num, e_num, e_index = 1;
int indegree[V_MAX], zero_in[STACK_MAX], zero_in_top = -1, result[STACK_MAX], result_top = -1;

void add_edge(int start, int end, int w) {
	next[e_index] = vertex[start];
	vertex[start] = e_index;
	edge[e_index] = end;
	weight[e_index++] = w;
}

void get_indegree_and_init_zeroin() {
	for(int i = 1; i <= e_num; ++i) {
		++indegree[edge[i]]; //initialise indegree array
	}
	for(int i = 1; i <= v_num; ++i) {
		if(!indegree[i]) //find the vertices whose in-degree is initially zero
			zero_in[++zero_in_top] = i; //push it into the zero_in stack
	}
}

void solve() {
	get_indegree_and_init_zeroin();

	while(zero_in_top != -1) {
		int cur = zero_in[zero_in_top--];
		result[++result_top] = cur;

		for(int j = vertex[cur]; j; j = next[j]) {
			--indegree[edge[j]]; //update indedgree array
			if(!indegree[edge[j]]) //if the vertex has no predecessor after operations above
				zero_in[++zero_in_top] = edge[j]; //add it to the zero_in stack
				//note: each vertex enters the zero_in stack at most once,
				// for indegree value will be rendered negative after updating an already-sorted vertex
				// and thus impossible to be pushed into zero_in stack.
		}
	}
	if(result_top != v_num - 1) printf("Circle exists!");
	else {
		for(int i = 0; i <= result_top; ++i)
			printf("%d ", result[i]);
	}
}

int main() {
	scanf("%d%d", &v_num, &e_num);
	for(int i = 1; i <= e_num; ++i) {
		int start, end, w;
		scanf("%d%d%d", &start, &end, &w);
		add_edge(start, end, w);
	}

	solve();

	return 0;
}
