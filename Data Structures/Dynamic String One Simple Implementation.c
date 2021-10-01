#include <stdio.h>
#include <stdlib.h>

/**
 * This program gives one implementation of the string.
 * The memory space of the string will be reallocated once
 *   its length is changed. So I call it a dynamic string.
 * The implementation is very simple even a little boring.
 * It is just for fun.
 */ 


typedef struct DynamicString {
	char *String;
	size_t Length;
} DynamicString, *PtrToDString;

void DStringInit(PtrToDString DS) {
	// Call DStringInit() before any operations on the dynamic string!!!
	DS->String = NULL;
	DS->Length = 0;
	printf("Dynamic String: Initialisation completed!\n");
}

void DStringDestroy(PtrToDString DS) {
	// Call DStringInit() before calling DStringDestroy()
	if(DS->String) free(DS->String);
	DS->Length = 0;
	printf("Dynamic String: Destruction completed!\n");
} //After calling DStringDestroy(), you need to call DStringInit() again before any operations on the dynamic string.

void DStringPrint(DynamicString DS) {
	for(int i = 0; i < DS.Length; ++i)
		putchar(DS.String[i]);
	printf("[END OF THE DYNAMIC STRING]\n");
}

void DStringAssign(PtrToDString DS, const char * CS) {
	if(DS->String) free(DS->String);

	if(CS == NULL) { 
		//CS = NULL means you want to reset the dynamic string
		DS->String = NULL;
		DS->Length = 0;
		return;
	}
	else {
		size_t length = 0;
		while(CS[length]) ++length; //calculate the length of the C-style string
		DS->String = (char *)malloc(length * sizeof(char));
		if(DS->String == NULL) {
			printf("Failed to get required memory space!\n");
			DS->Length = 0;
			return;
		}
		else {
			for(int i = 0; i < length; ++i)
				DS->String[i] = CS[i];
			DS->Length = length;
			printf("Dynamic String: assigned successfully!\n");
		}
	}
}

void DStringInsertBefore(PtrToDString DS, size_t index, DynamicString Insertion) {
	if(index > DS->Length) {
		printf("Illegal insertion point!\n");
		return;
	}
	else {
		char * temp = (char *)malloc((DS->Length + Insertion.Length) * sizeof(char));
		if(temp == NULL) {
			printf("Failed to get required memory space!\n");
			return;
		}
		else {
			int i = 0, j = 0, k = 0;
			while(i != index) temp[k++] = DS->String[i++];
			while(j < Insertion.Length) temp[k++] = Insertion.String[j++];
			while(i < DS->Length) temp[k++] = DS->String[i++];
			free(DS->String);
			DS->String = temp;
			DS->Length = k;
			printf("Insertion completed!\n");
		}
	}
}

void DStringDelete(PtrToDString DS, size_t begin, size_t end) {
	//delete the substring [begin, end) from the dynamic string DS
	if(begin >= end || end > DS->Length) {
		printf("Illegal interval!\n");
		return;
	}
	else {
		char * temp = (char *)malloc( (DS->Length - (end - begin) ) * sizeof(char));
		if(temp == NULL) {
			printf("Failed to get required memory space!\n");
			return ;
		}
		else {
			int i = 0, k = 0;
			while(i != begin) temp[k++] = DS->String[i++];
			while(i != end) ++i;
			while(i < DS->Length) temp[k++] = DS->String[i++];
			free(DS->String);
			DS->String = temp;
			DS->Length = k;
			printf("Deletion completed!\n");
		}
	}
}

void DStringConcat(PtrToDString DS, DynamicString Appendix) {
	printf("Concatenation implemented by insertion!\n");
	DStringInsertBefore(DS, DS->Length, Appendix);
}

size_t strlen(const char *str) {
	size_t length = 0;
	while(str[length]) ++length;
	return length;
}

int main() {
	DynamicString DS, Insertion;
	char input[128];
	fgets(input, 128, stdin);
	input[strlen(input) - 1] = 0;
	DStringInit(&DS);
	DStringInit(&Insertion);

	DStringAssign(&DS, input);
	DStringAssign(&Insertion, "[INSERTION]");
	printf("Length: %zd\n", DS.Length);
	DStringPrint(DS);
	DStringConcat(&DS, Insertion);
	DStringPrint(DS);
	DStringInsertBefore(&DS, 0, Insertion);
	DStringPrint(DS);
	DStringDelete(&DS, 1, 5);
	DStringPrint(DS);
	DStringInsertBefore(&DS, 3, Insertion);
	DStringPrint(DS);
	DStringDelete(&DS, 5, DS.Length);
	DStringPrint(DS);
	DStringDelete(&DS, 5, 99);
	DStringPrint(DS);

	DStringDestroy(&DS);
	DStringDestroy(&Insertion);
	return 0;
}