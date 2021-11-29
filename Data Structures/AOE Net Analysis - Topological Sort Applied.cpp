#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
	This program calculates an AOE net (see page 183 of the book).
	An AOE(Activity-On-Edge) net is a DAG (Directed Acycling Graph) which
	is useful in optimising projects by analysing which activities decide 
	the duration of the whole project. By minimizing delay of those 
	activities, the project can go more smoothly, thus the time comsumption 
	lessened. More details could be seen in the book and related materials.
	
	The idea of solving the earliest and latest times one activity starts is that 
	first we calculate the earliest and latest times one "node" starts, then we 
	do some simple math operations to get the solutions. The "node" here means the 
	intersection point of activities. Activities are on edges as the graph is named, 
	which are different from those on an AOV (Activity-On-Vertex) net.
	
	The formulas we use in this problem are as follows:
		ve[start] = 0;
		ve[j] = max( for all i as predecessor, ve[i] + duration(i, j) );
		vl[end] = ve[end];
		vl[i] = min( for all j as successor, vl[j] - duration(i, j) );
		
		ee[edge i] = ve[startint vertex of edge i];
		el[edge i] = vl[ending point of edge i] - duration(edge i);
*/

#define V_MAX 1004
#define E_MAX 10004
#define S_MAX 1024

// only one source vertex and one ending vertex in the graph!!

int v[V_MAX], e[E_MAX], nxt[E_MAX], w[E_MAX];
int v_num, e_num, e_index = 1;
int S[S_MAX], s_top = -1, T[S_MAX], t_top = -1;
int din[V_MAX];
int ve[V_MAX], vl[V_MAX], ee[E_MAX], el[E_MAX];
bool legal = true;

void add_edge(int start, int end, int weight) {
	nxt[e_index] = v[start];
	v[start] = e_index;
	e[e_index] = end;
	++din[end];
	w[e_index++] = weight;
}

void getve() {
	memset(ve, 0xff, sizeof(ve));
	
	int count = 0;
	for(int i = 1; i <= v_num; ++i)
		if(!din[i]) {
			S[++s_top] = i;
			ve[i] = 0;
		}
	
	while(s_top != -1) {
		int cur = S[s_top--];
		T[++t_top] = cur;
		++count;
		for(int j = v[cur]; j; j = nxt[j]) {
			if(--din[e[j]] == 0) S[++s_top] = e[j];
			if( ve[e[j]] == -1 || ve[e[j]] < ve[cur] + w[j]) {
				//check ve[...] == -1 to tell if ve[...] has been assigned a value.
				//for ve[...] may be zero!!!
				ve[e[j]] = ve[cur] + w[j];
			}
		}
	}
	
	if(count != v_num) {
		printf("Illegal graph!\n");
		legal = false;
		return;
	}
	
	for(int i = 1; i <= v_num; ++i) 
		printf("ve[%d] = %d\n", i, ve[i]);
}

void getvl() {
	memset(vl, 0xff, sizeof(vl));
	
	if(!legal) return;
	
	vl[T[t_top]] = ve[T[t_top]];
	--t_top;
	
	while(t_top != -1) {
		int cur = T[t_top--];
		for(int j = v[cur]; j; j = nxt[j]) {
			if(vl[cur] == -1 || vl[cur] > vl[e[j]] - w[j]) { 
				vl[cur] = vl[e[j]] - w[j]; 
			}
		}
	}
	
	for(int i = 1; i <= v_num; ++i) 
		printf("vl[%d] = %d\n", i, vl[i]);
}

int main() {
	scanf("%d%d", &v_num, &e_num);
	for(int i = 1; i <= e_num; ++i) {
		int start, end, weight;
		scanf("%d%d%d", &start, &end, &weight);
		add_edge(start, end, weight);
	}
	
	getve();
	getvl();
	
	for(int i = 1; i <= v_num; ++i) {
		for(int j = v[i]; j; j = nxt[j]) {
			ee[j] = ve[i];
			el[j] = vl[e[j]] - w[j];
		}
	}
	
	for(int i = 1; i <= e_num; ++i) {
		printf("edge %d: earliest: %d latest: %d key activity:%s\n", i, ee[i], el[i], (el[i] - ee[i] ? "no" : "yes") );
	}
	
	return 0;
}
