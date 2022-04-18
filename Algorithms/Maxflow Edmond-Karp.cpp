#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 220, M = 10010, INF = 0x7fffffff;
int ve[N], to[M], nxt[M], cap[M], idx;
int n, m, s, t;
int used[N], p[N], preseg[N], btnk[N];

void addedge(int a, int b, int cc) {
	to[idx] = b;
	cap[idx] = cc;
	nxt[idx] = ve[a];
	ve[a] = idx++;
}

int edmond_karp(int s, int t) {
	//do BFS instead of DFS on the basis of the idea of ford-fulkerson algorithm
	queue<int> q;
	used[s] = 1;
	q.push(s);
	
	bool found = false;
	while(!found && !q.empty()) {
		int v = q.front();
		q.pop();
		
		for(int j = ve[v]; ~j; j = nxt[j]) {
			if(!used[to[j] ] && cap[j] > 0) {
				p[to[j] ] = v;
				preseg[to[j] ] = j;
				btnk[to[j] ] = min(cap[j], btnk[v]);
				if(to[j] == t) {
					found = true;
					break;
				}
				used[to[j] ] = 1; //mark before pushing it into the queue
				q.push(to[j]);
			}
		}
	}
	
	int v = t, f = btnk[t];
	while(p[v]) {
		cap[preseg[v] ] -= f;
		cap[preseg[v] ^ 1] += f;
		v = p[v]; //don't forget
	}
	
	return (f == INF) ? 0 : f;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	
	memset(ve, -1, sizeof ve);
	for(int i = 1; i <= m; ++i) {
		int a, b, cc;
		scanf("%d%d%d", &a, &b, &cc);
		addedge(a, b, cc);
		addedge(b, a, 0); // capacity of the inverse edge is initially zero!!
	}
	ll flow = 0;
	int f;
	do {
		memset(used, 0, sizeof used); //used is used for marking visited vertices
		memset(p, 0, sizeof p); //p is used to mark the direct father of a vertex
		memset(preseg, -1, sizeof preseg); // preseg is used to mark the index of the edge pointing to the vertex
		//  -1 here will make sense
		for(int i = 1; i <= n; ++i)
			btnk[i] = INF; // btnk indicates the bottleneck capacity in a path from s to the vertex during BFS
		f = edmond_karp(s, t);
		flow += f;
	} while(f > 0);
	
	printf("%lld", flow);
	return 0;
}
