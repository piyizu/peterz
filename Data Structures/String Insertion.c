#include <stdio.h>
#include <string.h>

#define STRING_LENGTH_MAX 8
typedef struct String {
	size_t Length;
	char Contents[STRING_LENGTH_MAX];
} String, *PtrToString;

/**
 * Erhhhhhhhhhhhhhhh, this program simulates a string and its insertion function.
 * It is boring, but perhaps there is still something to learn.
*/

int mmin(int a, int b) {
	return (a < b) ? a : b;
}

void StringPrint(String *S) {
	for(int i = 0; i < S->Length; ++i)
		putchar(S->Contents[i]);
	printf("[END OF STRING]\n");
}

void StringInsertBefore(String *S, int Index, String *Insertion) {
	if(Index < 0 || Index > S->Length) {
		printf("Invalid position!\n");
		return;
	}
	else {
		S->Length = mmin(STRING_LENGTH_MAX, S->Length + Insertion->Length);
		for( int j = S->Length - 1, i = j - Insertion->Length; i >= Index; --j, --i)
			//Move the substring after the insertion point.
			S->Contents[j] = S->Contents[i];
		for(int i = Index, j = 0; i < STRING_LENGTH_MAX && j < Insertion->Length; ++i, ++j)
			//Insert the string and cut it when 'S' has no more space.
			S->Contents[i] = Insertion->Contents[j];
	}
}

void StringAssign(String *S, const char *CStr) {
	// Initialise the string with a C-style string
	int length = 0;
	while(length < STRING_LENGTH_MAX && CStr[length]) {
		S->Contents[length] = CStr[length];
		++length;
	}
	S->Length = length;
}

int main() {
	int index;
	String str, temp;
	char input1[STRING_LENGTH_MAX * 2], input2[STRING_LENGTH_MAX * 2];

	printf("Input a string:\n");
	fgets(input1, STRING_LENGTH_MAX * 2, stdin);
	input1[strlen(input1) - 1] = 0;
	StringAssign(&str, input1);
	StringPrint(&str);

	printf("Input the string to insert:\n");
	fgets(input2, STRING_LENGTH_MAX * 2, stdin);
	input2[strlen(input2) - 1] = 0;
	StringAssign(&temp, input2);
	StringPrint(&temp);

	printf("Now, input the index after the insertion point. The index is counted from 0:\n");
	scanf("%d", &index);
	StringInsertBefore(&str, index, &temp);
	StringPrint(&str);
	return 0;
}