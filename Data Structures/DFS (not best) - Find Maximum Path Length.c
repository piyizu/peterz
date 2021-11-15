#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V_MAX 1004
#define E_MAX 10004
#define STACK_MAX 1024

int v[V_MAX], e[E_MAX], nxt[E_MAX], w[E_MAX], mpl[V_MAX];
int v_num, e_num, e_index = 1;
int path[STACK_MAX], pathtop = -1, total_length;

void add_edge(int start, int end, int weight) {
	nxt[e_index] = v[start];
	v[start] = e_index;
	e[e_index] = end;
	w[e_index++] = weight;
}

void dfs(int vtex, int* mpl, int arclength) {
	for (int i = 0; i <= pathtop; ++i)
		if (path[i] == vtex)
			return;
	total_length += arclength;
	if (total_length > *mpl)
		*mpl = total_length;
	path[++pathtop] = vtex;
	for (int j = v[vtex]; j; j = nxt[j]) {
		dfs(e[j], mpl, w[j]);
	}
	total_length -= arclength;
	--pathtop;

}

void solve() {
	for (int i = 1; i <= v_num; ++i) {
		pathtop = -1;
		dfs(i, &mpl[i], 0);
	}
}

int main() {
	scanf("%d%d", &v_num, &e_num);
	for (int i = 1; i <= e_num; ++i) {
		int start, end, weight;
		scanf("%d%d%d", &start, &end, &weight);
		add_edge(start, end, weight);
	}

	solve();

	for (int i = 1; i <= v_num; ++i) {
		printf("%d: mpl = %d\n", i, mpl[i]);
	}

	return 0;
}