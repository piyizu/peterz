#include <iostream>
#include <cstdio>
#include <cstring>

/*
	version 0.2
	
	Input notes:
	n is the number of logical variables
	m is the number of sub-expressions
	phi indicates the expression
	     X5 ---> 5
	 NOT X5 ---> -5
	 
*/

using namespace std;

const int N = 20, M = 100 * 3;

int x[N], phi[M], n, pn;

int abs(int x) {
	return (x < 0) ? -x : x;
}

int check() { // 1: phi(x)=true  0: phi(x)=false -1:we do not know now
	bool uncertain = false;
	for(int k = 1; k <= pn; k += 3) {
		int numOfZero, numOfOne, numOfDefault;
		numOfZero = numOfOne = numOfDefault = 0;
		for(int i = 0; i <= 2; ++i) {
			if(x[abs(phi[k + i])] == -1) ++numOfDefault;
			else if(phi[k + i] < 0) {
				if(x[abs(phi[k + i])]) ++numOfZero;
				else {
					++numOfOne;
					break;
				}
			}
			else {
				if(!x[abs(phi[k + i])]) ++numOfZero;
				else {
					++numOfOne;
					break;
				}
			}
		}
		if(numOfDefault) uncertain = true;
		else if(!numOfOne) return 0;
	}
	if(uncertain) return -1;
	else return 1;
}

bool three_cnt() {
	memset(x, -1, sizeof x);
	
	int k = 1;
	bool backward = false; //indicate whether the current state is got by backtracking.
	while(k > 0 && k <= n) {
		// first try x_k = 1 then x_k = 0 then go back
		if(x[k] == -1) x[k] = 1;
		
		int ret;
		if(!backward) {
			ret = check();
			if(ret == 1) return true;
			else if (ret == 0) {
				if(x[k] == 1) x[k] = 0;
				else {
					x[k] = -1;
					--k;
					backward = true;
				}
			}
			else ++k;
		}
		else {
			if(x[k] == 1) {
				x[k] = 0;
				backward = false;
			}
			else {
				x[k] = -1;
				--k;
			}
		}
	}
	return false;
}

int main() {
	int m;
	
	FILE *fp = fopen("./in.txt", "r");
	while( fscanf(fp, "%d%d", &n, &m) == 2 ) {
		pn = 3 * m;
		for(int i = 1; i <= pn; ++i)
			fscanf(fp, "%d", &phi[i]);
		
		for(int i = 1; i <= m; ++i) {
			printf("(");
			for(int j = 1; j <= 3; ++j) {
				if(phi[3 * (i - 1) + j] < 0) printf(" ~");
				else printf(" ");
				 
				printf("x%d ", abs(phi[3 * (i - 1) + j]) );
				if(j != 3) printf("V");
			}
			printf(")");
			if(i != m) printf("/\\");
		}
		puts("");
		
		if(three_cnt()) {
			printf("Satisfiable <--- ");
			for(int i = 1; i <= n; ++i) {
				printf("x%d=", i);
				if(x[i] == -1) printf("Either, ");
				else printf("%d, ", x[i]);
			}
		}
		else printf("Unsatisfiable");
		puts("\n");
	}
	return 0;
}


/*
test input

4
3
1 -1 -2    3 2 4    -1 -3 -4
5
6
1 2 5    4 1 -3   3 -4 5    -2 4 5    1 3 5   2 -4 3
5
18
-1 -2 -3    3 4 -5    2 -4 5    -1 -2 3    -2 -3 4    -1 -4 5    1 3 -5
-1 2 3    1 -3 -4    -1 2 4    -1 3 -4    -1 4 5    -2 -3 5    -2 -4 5
-2 3 5    1 -2 -3    1 -2 4    3 4 5
3
8
1 2 3    1 2 -3    1 -2 3    1 -2 -3    -1 2 3    -1 2 -3    -1 -2 3    -1 -2 -3

*/
