#define _CRT_SECURE_NO_WARNINGS
/*
	As is defined, the matrix multiplication requires time of O(ra*cb*ca) to complete.
	This program implements the multiplication of two matrices using arrays. You should be
	quite aware that the matrices may contain many non-zero items. Therefore, the application
	of cross-road linked list or other related structures may not work as well as expected.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int ra, ca;
	scanf("%d%d", &ra, &ca);
	int* ma = (int*)malloc(ra * ca * sizeof(int));
	if (ma == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < ra; ++i) {
		for (int j = 0; j < ca; ++j)
			scanf("%d", &ma[i * ca + j]); 
		//Attention: You should not replace ma[..] with ma[i][j], for ma is not
		// defined as a two-dimension array. Actually it is not at all an array.
		// We just use it as an array.
	}

	int rb, cb;
	scanf("%d%d", &rb, &cb);
	int* mb = (int*)malloc(rb * cb * sizeof(int));
	if (mb == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < rb; ++i) {
		for (int j = 0; j < cb; ++j)
			scanf("%d", &mb[i * cb + j]);
	}

	if (ca != rb) {
		printf("Error: %d != %d\n", ca, rb);
		//Check if matrix multiplication is legal under the given matrices.
	}
	else {
		int* mr = (int*)malloc(ra * cb * sizeof(int));
		if (mr == NULL) exit(EXIT_FAILURE);

		for (int i = 0; i < ra; ++i) {
			for (int j = 0; j < cb; ++j) {
				mr[i * cb + j] = 0;
				for (int k = 0; k < ca; ++k)
					mr[i * cb + j] += ma[i * ca + k] * mb[k * cb + j];
			}
		}
		printf("%d %d\n", ra, cb);
		for (int i = 0; i < ra; ++i) {
			for (int j = 0; j < cb; ++j) {
				printf("%d", mr[i * cb + j]);
				if (j < cb - 1) putchar(' ');
			}
			if (i < ra - 1)
				printf("\n");
		}

		free(mr);
	}
	// Remember to free the allocated memory space.
	free(mb);
	free(ma);

	return 0;
}
