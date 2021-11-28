#include <cstdio>
#include <cmath>
#include <cstdlib>

/* This program shows the implementation and application of 
 a secondarily optimal static binary search tree.

	The secondarily optimal static binary search tree is for 
 accelerating the searching of ordered values in an array, which
 have different probabilities of being searched. The SOSBST is not
 the best BST for solving this problem, but it gives a simple as 
 well as fast way. Here it comes.
*/

#define AR_MAX 1004

struct sstree_node{
	int val, pos;
	sstree_node * left, * right;
} *sstree;

struct content{
	int val, weight;
} ar[AR_MAX];

int n, psum[AR_MAX], diff[AR_MAX];

sstree_node * build_sstree(int l, int r) {
	if(l > r) return NULL; // special judge is of great importance
	
	int min = 0x7fffffff, minindex = 0;
	for(int i = l; i <= r; ++i) { //find the root
		diff[i] = abs(psum[r] - psum[i] - psum[i - 1] + psum[l - 1]);
		if(diff[i] < min) {
			min = diff[i];
			minindex = i;
		}
	}
	
	sstree_node * temp = (sstree_node *) malloc(sizeof(sstree_node));
	if(temp == NULL) exit(EXIT_FAILURE);
	
	temp->val = ar[minindex].val;
	temp->pos = minindex;
	temp->left = build_sstree(l, minindex - 1);
	temp->right = build_sstree(minindex + 1, r);
	
	return temp;
	
}

void traversal(sstree_node *p) {
	if(p) {
		printf("%c ", p->val);
		traversal(p->left);
		traversal(p->right);
	}
}

int search(int val, sstree_node *p) {
	int temp;
	
	if(p->val == val) return p->pos;
	else {
		if(p->left) if(temp = search(val, p->left)) return temp;
		if(p->right) if(temp = search(val, p->right)) return temp;
	}
	return 0; //not found
}

void destroy(sstree_node *p) {
	if(p) {
		destroy(p->left);
		destroy(p->right);
		free(p);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%*c%c", &ar[i].val);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &ar[i].weight);
		psum[i] = psum[i - 1] + ar[i].weight;
		//prefix partial sum
	}
	psum[n + 1] = psum[n]; 
	//add a virtual element forwards for easily dealing with build_sstree(k, k+1) situations
	//this is also the reason for starting from 1 instead of 0.
	
	sstree = build_sstree(1, n); //build a static search tree for ar[1...n]
	
	traversal(sstree);
	printf("\n");
	
	int to_find;
	scanf("%*c%c", &to_find);
	if(to_find = search(to_find, sstree)) printf("Position: %d", to_find);
	else printf("Not found!");
	
	destroy(sstree);
	
	return 0;
}
