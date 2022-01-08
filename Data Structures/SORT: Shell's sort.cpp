#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
  Problem description has been given. Shell's sort (Diminishing Increment Sort) is applied in this program.
*/

#define SIZEMAX 100004
#define DELTAMAX 12

int main() {
	srand((unsigned int)time(NULL));
	int n, ar[SIZEMAX];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		ar[i] = int( double(rand())/RAND_MAX * 10000);
	
	for(int i = 0; i < n; ++i) {
		printf("%d ", ar[i]);
	}
	putchar('\n');
	
	int m, delta[DELTAMAX]; // the sequence of delta. please make sure that delta[m-1] = 1;
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", &delta[i]);
	
	for(int i = 0; i < m; ++i) { // for each delta
		for(int j = 0; j < delta[i]; ++j) { //for each subsequence
			for(int k = j + delta[i]; k < n; k += delta[i]) { //for one subsequence, simple insertion sort
				int temp = ar[k], l = k - delta[i];
				while(l >= 0 && ar[l] > temp) { // be careful of the boundaries
					ar[l + delta[i]] = ar[l]; 
					l -= delta[i];
				}
				ar[l + delta[i]] = temp;
			}
		}
	}
	
	for(int i = 0; i < n; ++i) {
		printf("%d", ar[i]);
		if(i != n - 1) putchar(' ');
	}
	
	
	return 0;
}
