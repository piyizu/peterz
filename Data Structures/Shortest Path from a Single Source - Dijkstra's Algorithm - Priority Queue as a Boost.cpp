#include <iostream>
#include <queue>

/*
	This is a program showing how Dijkstra's Shortest Path Algorithm for a single
source point works. It uses a priority queue (which is implemented using something 
 like a heap) to accelerate the finding of the next vertex to choose.
 
 	The program combines two key topics of data structures and algorithms, the
 Dijkstra's Shortest Path Algorithm and the heap structure.
  
 	A heap is an important data structure that can be implemented with a complete 
 binary tree. And a complete binary tree has good properties that make it easy 
 to be simulated with an array. The problem of shortest paths is solved with the
 help of the standard C++ template library. The solution would be greater if it is 
 realised with the simulation of heap using arrays. Though I tried that, I failed and 
 I now have no more time...
*/

#define V_MAX 100004
#define E_MAX 200004
#define INF 0x7fffffff

struct queue_node{
	int dis, pos;
	bool operator<(const queue_node & t) const {
		return t.dis < dis;
	}
}cur;

std::priority_queue<queue_node> q;

int v[V_MAX], e[E_MAX], nxt[E_MAX], w[E_MAX];
int v_num, e_num, e_index = 1;
int d[V_MAX], s[V_MAX];

void add_edge(int start, int end, int weight) {
	nxt[e_index] = v[start];
	v[start] = e_index;
	e[e_index] = end;
	w[e_index++] = weight;
}

void dij(int start) {
	for(int i = 0; i <= v_num; ++i)
		d[i] = INF;
	d[start] = 0;
	q.push({d[start], start}); //push it into the priority queue
	//Note: the priority queue is only for finding, not for keeping the results!
	
	while(!q.empty()) {
		cur = q.top();
		q.pop();
		if(s[cur.pos]) continue; //this is one of the simplest ways to deal with repeated pushed vertices
		else s[cur.pos] = 1;
		
		for(int i = v[cur.pos]; i; i = nxt[i]) {
			if(d[e[i]] == INF || d[e[i]] > cur.dis + w[i]) {
				d[e[i]] = cur.dis + w[i];
				q.push({d[e[i]], e[i]});
			}
		}
	}
	
	for(int i = 1; i <= v_num; ++i)
		printf("%d ", d[i]);
	
}

int main() {
	int start;
	scanf("%d%d%d", &v_num, &e_num, &start);
	for(int i = 1; i <= e_num; ++i) {
		int start, end, weight;
		scanf("%d%d%d", &start, &end, &weight);
		add_edge(start, end, weight);
	}
	
	dij(start);
	
	return 0;
}
