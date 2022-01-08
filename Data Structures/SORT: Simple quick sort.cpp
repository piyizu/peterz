#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
  Problem description has been given. Quick sort, as it is named, is quick (however not always the quickest).
*/

#define SIZEMAX 100004

int partition(int *ar, int l, int r) {
	// dual pointer method, the best way to do partition!
	int pivot = ar[l];
	while(l < r) {
		while(l < r && ar[r] >= pivot) --r;
		ar[l] = ar[r];
		while(l < r && ar[l] <= pivot) ++l;
		ar[r] = ar[l];
	}
	ar[l] = pivot;
	return l;
}

void myquicksort(int *ar, int l, int r) {
	if(l < r) {
		int p = partition(ar, l, r);
		myquicksort(ar, l, p - 1);
		myquicksort(ar, p + 1, r);	
	}
}

int main() {
	srand((unsigned int)time(NULL));
	int n, ar[SIZEMAX];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		//ar[i] = int( double(rand())/RAND_MAX * 10000);
		scanf("%d", &ar[i]);
	
	myquicksort(ar, 0, n - 1);
	
	for(int i = 0; i < n; ++i) {
		printf("%d", ar[i]);
		if(i != n - 1) putchar(' ');
	}
	
	
	return 0;
}
