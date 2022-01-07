/*
  In this program, we will verify the formula for counting a statement within a nested loop.
  The statement is marked by @ in the code and we calculate theoretically that T(n) = 1/6*n*(n+1)*(n+2) in our program.
  Run the program and you can see the results.
  You can also see that T(n) = 1/24*n*(n+1)*(n+2)*(n+3) works for a 4-nested loop by slightly changing the code.
  
  NOTE: T(n) may exceed the integer implementaion limit!
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
	srand((unsigned int)time(NULL));
	printf("  N        COUNT    THEORETICAL RESULT   ERROR\n");
	for(int n = 100; n <= 1000; n += rand()%100) {
		int count = 0;
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= i; ++j) {
				for(int k = 1; k <= j; ++k){
					++count; //@
				}
			}
		}
		int res = (int)( ((unsigned long long)n)*(n+1)*(n+2)/6 );
		printf("%4d %12d       %10d    %6d\n", n, count, res, count - res);
	}
	return 0;
}
