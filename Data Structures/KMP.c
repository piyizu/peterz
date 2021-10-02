#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE_MAX 128

/** KMP
 *  Pattern matching problem is one of the most interesting things about 
 * strings. The Knuth-Morris-Pratt Operation, aka the KMP method, is 
 * a fantastic algorithm for pattern matching. Here, with the help of the
 * textbook, I translates the ideas of the algorithm to C code.
 *  Great journey will not be accomplished without actual steps. This program
 * is just a small step on my journey of leaning algorithms.
 * */

typedef enum status{
	success, failure
} status;

void NextGenerator(const char * pattern, int * next) {
	next[0] = -1;
	int i = 0, j = -1;
	int pattern_length = strlen(pattern);
	while(i < pattern_length && j < pattern_length) {
		// next[i] has been assigned a value when entering the loop
		if(j == -1 || pattern[i] == pattern[j]) {
			// if 'p[0]p[1]...p[j]' matches 's[i-j]s[i-j+1]...s[i]', j+1 is
			// exactly the value of next[i+1].
			// if j is -1, next[i+1] should be 0 for no such shoter pattern matches 
			// any one of substrings ending with 's[i-1]'. 
			++i;
			++j;
			next[i] = j;
		}
		else {
			// if j is not -1 and p[j] does not match s[i], set j to next[j] so that
			// 'p[0]p[1]...p[j'-1]' will be the longest shorter pattern matching the substring 
			// of the same length ending with s[i -1].
			j = next[j];
		} 
	}
}

status KMP(const char * string, const char * pattern, int * next) {
	int i = 0, j = 0;
	int slength = strlen(string), plength = strlen(pattern);
	while(i < slength && j < plength) {
		if(j == -1 || string[i] == pattern[j]) {
			// if 's[i-j]s[i-j+1]...s[i]' == 'p[0]p[1]...p[j]' or 
			// no shorter pattern matches any substring ending with 's[i]', 
			// increase both i and j. 
			++i;
			++j;
		}
		else 
			// if 's[i-j]s[i-j+1]...s[i-1]' matches 'p[0]p[1]...p[j-1]' but
			// s[i] != p[j], set j to next[j] such that the longest shorter pattern 
			// 'p[0]p[1]...p[j'-1]' matches 's[i-j']s[i-j'+1]...s[i-1]'.
			// it will save the time.
			j = next[j];
	}
	if(j == plength) return success;
	else return failure;
}

int main() {
	char input[STRING_SIZE_MAX], pattern[STRING_SIZE_MAX];
	int next[STRING_SIZE_MAX] = {1,2,3,4};
	printf("Please input the pattern string:\n");
	fgets(pattern, STRING_SIZE_MAX, stdin);
	pattern[strlen(pattern) - 1] = 0;
	NextGenerator(pattern, next);

	int length = strlen(pattern);
	printf("INDEX:");
	for(int i = 0; i < length; ++i)
		printf("%+-4d", i);
	putchar('\n');
	printf("CHARS:");
	for(int i = 0; i < length; ++i)
		printf(" %-3c", pattern[i]);
	putchar('\n');
	printf("NEXT :");
	for(int i = 0; i < length; ++i)
		printf("%+-4d", next[i]);
	putchar('\n');

	printf("Now input the source string:\n");
	fgets(input, STRING_SIZE_MAX, stdin);
	input[strlen(input) - 1] = 0;

	if(KMP(input, pattern, next) == success) printf("MATCHED SUBSTRING FOUND!\n");
	else printf("NO MATCHED SUBSTRING\n");
	return 0;
}