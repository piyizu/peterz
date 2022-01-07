#include <cstdio>
#include <cstdlib>

/*Problem description can be seen in the SORT: Simple insertion sort.cpp*/

#define SIZEMAX 100004

int main() {
	int n, ar[SIZEMAX];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &ar[i]);
	
	for(int i = 1; i < n; ++i) {
		/*Binary search applied in searching the insertion point
			NOTE: all elements after the point are larger than and 
			all elements before are less than or equalled to the element to insert.
		*/
		int l = 0, r = i - 1, temp = ar[i];
		while(l <= r) {
			int mid = l + r >> 1;
			if(ar[mid] > temp) r = mid - 1; //////
			else l = mid + 1;
		}
		
		int j;
		for(j = i - 1; j >= l; --j)
			ar[j + 1] = ar[j];
		ar[j + 1] = temp;
	}
	
	for(int i = 0; i < n; ++i) {
		printf("%d", ar[i]);
		if(i != n - 1) putchar(' ');
	}
	return 0;
}
