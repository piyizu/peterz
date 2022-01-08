#include <cstdio>
#include <cstdlib>
#include <ctime>

#define SIZEMAX 100004

struct listnode{
	int val, next;
};

int main() {
	srand((unsigned int)time(NULL));
	int n;
	struct listnode ar[SIZEMAX];
	scanf("%d", &n); // n elements
	for(int i = 1; i <= n; ++i) //rendom numbers generator
		ar[i].val = int( double(rand())/RAND_MAX * 10000);
	ar[0].next = 1;
	ar[1].next = 0;
	
	for(int i = 2; i <= n; ++i) { // Insert the elements to the list
		int j = 0;
		
		while (ar[j].next && ar[ ar[j].next ].val <= ar[i].val) j = ar[j].next;
		
		ar[i].next = ar[j].next;
		ar[j].next = i;
	}
	
	for(int i = 1, j = ar[0].next; i <= n; ++i) {
    // now ar[0 .. i-1] has been arranged
		while(j && j < i) j = ar[j].next; 
    // if j points to a position in [0, i-1], the original record has been moved to ar[j].next.
		int next_in_sequence = ar[j].next;
    // next_in_sequence keeps the next record in the sequence, which may be lost after swapping values.
		
		if(j && j != i) {
      //j!=i, then ar[j] is not arranged correctly, neither is ar[i] (indicating that ar[i] is not the i-th in the sequence and it should be larger),
      // so swap them and ar[i] will be in the right place.
			struct listnode temp = ar[i];
			ar[i].val = ar[j].val;
			ar[i].next = j;
			ar[j].val = temp.val;
			ar[j].next = temp.next;
		}
		j = next_in_sequence;
    //NOTE: after swapping, the original linkings are no longer available, 
    // so do not use ar[..] as a linked list after the arrangement.
	}
	
	for(int i = 1; i <= n; ++i) {
		printf("%d", ar[i].val);
		if(i != n) putchar(' ');
	}
	
	return 0;
}
