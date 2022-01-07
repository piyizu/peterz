#include <cstdio>
#include <cstdlib>

/*
	Problem description is in SORT: Simple insertion sort.cpp
	
	The 2-path insertion sort uses two pointers: the beforefirst and the final
	to indicate the position BEFORE the first element in the sorted list and 
	the last element OF the list. We insert the element that less than ar[0] before
	ar[0] and others after ar[0] (looks like ar[0] is the dividing point of the list).
	To minimize space usage, in this program we use two pointers so that one array 
	can be used as two lists. Details can been seen in the comments.
*/

#define SIZEMAX 100004

int main() {
	int n, ar[SIZEMAX];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &ar[i]);
	
	int beforefirst = n - 1, final = 0;
	for(int i = 1; i <= beforefirst; ++i) {
		int temp = ar[i];
		
		if(temp < ar[0]) {
			ar[i--] = ar[beforefirst]; 
			//swap for insertion. ar[i] after the insertion is not sorted.
			// decreasing i so that ar[i] would not be skipped. 
			ar[beforefirst] = temp; //this line can be cancelled.
			
			int j;
			for(j = beforefirst + 1; j < n && ar[j] <= temp; ++j)
				ar[j - 1] = ar[j];
			ar[j - 1] = temp; 
			// (j - 1) is the insertion point after the loop due to ++j's effect
			--beforefirst;
		}
		else {
			// Do as in simple insertion sort
			int j;
			for(j = final; j > 0 && ar[j] > temp; --j)
				ar[j + 1] = ar[j];
			ar[j + 1] = temp;
			++final;
		}
	}
	
	for(int i = beforefirst + 1; i < n; ++i)
		printf("%d ", ar[i]);
	for(int i = 0; i <= final; ++i) {
		printf("%d", ar[i]);
		if(i != final) putchar(' ');
	}
	return 0;
}
