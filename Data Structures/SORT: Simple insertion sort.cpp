#include <cstdio>
#include <cstdlib>

/*
  Given number n and n numbers, sort them and print them out separated by blanks. 
*/

#define SIZEMAX 100004

int main() {
	int n, ar[SIZEMAX];
	scanf("%d", &n);
	
	for(int i = 0; i < n; ++i)
		scanf("%d", &ar[i]);
	
	for(int i = 1; i < n; ++i) {
		int temp = ar[i], j;
    //currently ar[0...i-1] has been sorted.
		for(j = i - 1; j >= 0 && ar[j] > temp; --j) //move the elements forwards and find the position to insert
				ar[j + 1] = ar[j];
		ar[j + 1] = temp; //NOTE that now j is either -1 or the position before the insertion point.
	}
	
	for(int i = 0; i < n; ++i) {
		printf("%d", ar[i]);
		if(i != n - 1) putchar(' ');
	}
	return 0;
}
