/* in.txt

n m
a_1 b_1 cap_1
a_2 b_2 cap_2
...
a_m b_m cap_m
s t

n vertices (1 ~ n) in the graph, 
m directed edges (no need to consider the reverse edges),
m capabilities
source vertex s
sink vertex t


One example :

4 5
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40
4 3
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, M = 10010; //vertex and edge number limits.
//NOTE: the edge limit should be TWICE the MAXIMUM of edges
const int INF = 0x3f3f3f3f;
//NOTE: you can change INF to any larger value,
// but make sure it should not exceed the int limit
// and you handle it correctly in the program

int ve[N], to[M], rev[M], nxt[M], cap[M], idx;
int n, m, s, t;
int used[N];

void addedge(int a, int b, int capp) {
	to[idx] = b;
	cap[idx] = capp;
	nxt[idx] = ve[a];
	ve[a] = idx;
	rev[idx] = ++idx; ///rev[idx]= idx++ results in infinite loop

	rev[idx] = idx - 1;
	to[idx] = a;
	cap[idx] = 0;
	nxt[idx] = ve[b];
	ve[b] = idx++;
}

int dfs(int v, int f) {
	if(v == t) return f;
	used[v] = 1; // indicates that the vertex has been visited
	
	for(int j = ve[v]; ~j; j = nxt[j]) {
		if( !used[to[j] ] && cap[j] > 0 ) {
			// if there is a potential edge of an augmented path in the current residual network
			// do DFS on that edge
			int r = dfs(to[j], min(f, cap[j]) );
			if(r > 0) {
				// if the bottleneck flow is positive,
				// which means that the augmented path is legal, then do as follows
				cap[j] -= r;
				cap[rev[j] ] += r; //remember to add flow to the reverse egde capabilities
				//one clever way to change the cap of the reverse edge is cap[j ^ 1] += r
				//but make sure that reverse edges are adjacent to each other
				return r;
			}
		}
	}
	
	return 0;
}

int main() {
	FILE *fp = fopen("./in.txt", "r");
	if(!fp) exit(1);
	
	memset(ve, -1, sizeof ve);
	fscanf(fp, "%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		int a, b, capp;
		fscanf(fp, "%d%d%d", &a, &b, &capp);
		addedge(a, b, capp);
	}
	fscanf(fp, "%d%d", &s, &t);
	
	printf("%d->%d, ", s, t);
	
	int flow = 0, f;
	do {
		memset(used, 0, sizeof used);
		f = dfs(s, INF);
		flow += f;
		/*printf("f = %d, flow = %d\n", f, flow);
		for(int i = 1; i <= n; ++i) {
			printf("%d", used[i]);
		}
		puts("");
		for(int i = 0; i < 2 * m; ++i)
			printf("%d ", cap[i]);
		puts("");*/
	} while(f > 0);
	
	printf("MAX_FLOW = %d\n", flow);
	
	return 0;
}
