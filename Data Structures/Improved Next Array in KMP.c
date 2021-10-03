#include <stdio.h>
#include <string.h>

#define STRING_SIZE_MAX 128

/**
 * This program improves the Next Array in KMP pattern matching.
 *  For example, in pattern p = 'caaaaaaab', if p[7] does not match, according to
 * the original Next Array, it should test if p[6] matches. However, there is obviously
 * no need to do that, for p[6] = p[7], matching is impossible.
 * With the improved Next Array, the program will skip all the consecutively repeated charcters
 *  and get the Next value of the first of those character. See how it is implemented:
 * */

void GetFixedNext(const char * String, int * Next) {
	Next[0] = -1;
	int i = 0, j = -1, length = strlen(String);
	while(i < length - 1) {
		if(j == -1 || String[i] == String[j]) {
			++i;
			++j;
			if(String[i] == String[j]) 
			// Before assign the Next value, check if the j will cause such useless work. 
				Next[i] = Next[j];
			else
				Next[i] = j;
		}
		else j = Next[j];
	}
}

int main() {
	char input[STRING_SIZE_MAX];
	int next[STRING_SIZE_MAX], length;

	fgets(input, STRING_SIZE_MAX, stdin);
	input[strlen(input) - 1] = 0;
	length = strlen(input);

	GetFixedNext(input, next);

	for(int i = 0; i < length; ++i)
		printf("%-3c", input[i]);
	putchar('\n');
	for(int i = 0; i < length; ++i)
		printf("%-3d", next[i]);
	putchar('\n');

	return 0;
}