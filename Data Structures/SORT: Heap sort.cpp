#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
	Heap sort is a sorting algorithm using the data structure heap.
	The main idea to build a heap is to adjust each node of the 
	complete binary tree level by level from bottom to top.
	To pick the max/min value from the heap, we swap the top node with the last one 
	and shift down the top and drop the last one.
	In this heap sort program, we make the top of heap be the largest
	element of the heap.
*/

/* AMAZING! This is the fastest sorting algorithm for cases on pintia.cn.
	The average time consumption is less than 30ms for about 10^5 random numbers.
*/

#define SIZEMAX 100004

void shiftdown(int *heap, int top, int bottom) {
	if(top >= bottom) return;
	// The top of the heap need to be put in the right position
	int val = heap[top], j;
	for(j = top * 2; j <= bottom; j = j * 2) {
		if(j + 1 <= bottom && heap[j + 1] > heap[j]) ++j; 
		// make j points to the largest child of node j/2
		if(heap[j] <= val) break; 
		// if the largest child is no larger than val, j/2 would be the position to put val.
		// heap[j] < val may cause time limit exceeded problem
		heap[j / 2] = heap[j];
		// if the largest child is larger than val, put it to node j/2, 
		// now val is temporarily in node j, but we do not actually copy it there
	}
	heap[j / 2] = val;
}

int main() {
	srand((unsigned int)time(NULL));
	int n, ar[SIZEMAX];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		//ar[i] = int( double(rand())/RAND_MAX * 10000);
		scanf("%d", &ar[i]);
	
	for(int i = n / 2 - 1; i >= 0; --i) {
		shiftdown(ar, i, n - 1);
		// Adjust the array to be a heap, using the complete binary tree model.
	}
	for(int i = n - 1; i > 0; --i) {
		//pick the largest from [0...i] and put it back:
		ar[i] ^= ar[0];
		ar[0] ^= ar[i];
		ar[i] ^= ar[0];
		// adjust [0... i-1] to be a heap.
		shiftdown(ar, 0, i - 1);
	}
	
	for(int i = 0; i < n; ++i) {
		printf("%d", ar[i]);
		if(i != n - 1) putchar(' ');
	}
	
	
	return 0;
}
