#define _CRT_SECURE_NO_WARNINGS

/*
* This program analyses a source file of C code. It calculates the number
* of lines in the file and the average length of the functions.
* It will assess the quality of the code with grades.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE_MAX 128

typedef enum status {
	success, failure
} status;

status LoadFile(const char* FileName, char** Source) {
	FILE* fp = fopen(FileName, "rb");
	if (fp == NULL) return failure;

	fseek(fp, 0L, SEEK_END);
	long Length = ftell(fp) + 4L;
	fclose(fp);

	fp = fopen(FileName, "r");
	if (fp == NULL) return failure;

	char *ch = *Source = (char*)malloc(Length * sizeof(char));
	if (*Source != NULL) {
		while (!ferror(fp)) {
			if (!feof(fp))
				*(ch++) = fgetc(fp);
			else
				return success;
		}
		printf("Errors occur when reading the file!\n");
	}
	else
		printf("Memory allocation failure!\n");
	return failure;
}

void CountElement(char* Source, int* CodeLine, int* CommentLine, int* BlankLine, int* TotalLine, int *Function, double *AvgFunLength) {
	*CodeLine = *CommentLine = *BlankLine = *TotalLine = *Function = 0;
	*AvgFunLength = 0.0;
	bool HeadOfLine = true;
	char *ch = Source, *end = Source + strlen(Source);
	int Top = -1; //used to count the number of functions
	int FunStart; //used to calculate the length of the function
	while (ch < end) {
		// brackets matching test
		if (*ch == '{') {
			if (Top == -1) {
				FunStart = *CodeLine;
			}
			++Top;
		}
		if (*ch == '}') {
			if (Top != -1) {
				--Top;
				if (Top == -1) {
					++* Function;
					*AvgFunLength += (double)*CodeLine - (double)FunStart;
				}
			}
			else printf("Check your code! There might be some errors!\n");
		}

		//head of line test
		if (HeadOfLine) {
			++* TotalLine;

			if (*ch == '\n') { //if the first character of a line is '\n', it must be a blank line!
				++* BlankLine;
				++ch;
				continue; //avoid rendering HeadOfLine false and moving ch twice
			}

			if (*ch == '/') {
				if (*(ch + 1) == '/') {
					while (ch != end && *(ch++) != '\n') continue;
					//go to the end of the line or end of the file
					// ch now points at EOF or the first character of the next line.
					++* CommentLine;
					continue; //avoid rendering HeadOfLine false and moving ch twice
				}
			}

			++* CodeLine;
			HeadOfLine = false;
		}
		else {
			if (*ch == '\n') // end of line test
				HeadOfLine = true;
		}

		++ch; // move pointer ch forwards
	}
	*AvgFunLength /= *Function;

	free(Source); // free the space which the source file occupies.
}

void PrintResult(const char *FileName, int CodeLine, int CommentLine, int BlankLine, int TotalLine, int Function, double AvgFunLength) {
	printf("Beep~Beep~!\n");
	printf("The result of analysing source file \" %s \" :\n", FileName);
	printf("Length of Code:%d\nLength of Comments:%d\nBlank Lines:%d\nEffective Lines:%d\nNumber of Functions:%d\n"
		"Average Function Length:%g\n\n", TotalLine, CommentLine, BlankLine, CodeLine, Function, AvgFunLength);
	double EffectivePercentage = (double)CodeLine / (double)TotalLine;
	double CommentsPercentage = (double)CommentLine / (double)TotalLine;
	double BlankPercentage = (double)BlankLine / (double)TotalLine;
	printf("Effective Lines: *, Comment Lines: +, Blank lines: -\n[");
	for (int i = 1; i <= 78 * EffectivePercentage; ++i)
		putchar('o');
	for (int i = 1; i <= 78 * CommentsPercentage; ++i)
		putchar('+');
	for (int i = 1; i <= 78 * BlankPercentage; ++i)
		putchar('-');
	printf("]\n");

	if (AvgFunLength < 5 || AvgFunLength > 24)
		printf("Grade D: Bad routine size style.\n");
	else if (AvgFunLength < 7 || AvgFunLength > 21)
		printf("Grade C: Acceptable routine size style.\n");
	else if (AvgFunLength < 9 || AvgFunLength > 16)
		printf("Grade B: Good routine size style.\n");
	else
		printf("Grade A: Excellent routine size style.\n");

	if (CommentsPercentage < 0.05 || CommentsPercentage > 0.35)
		printf("Grade D: Bad commenting style.\n");
	else if (CommentsPercentage < 0.09 || CommentsPercentage > 0.31)
		printf("Grade C: Acceptable commenting style.\n");
	else if (CommentsPercentage < 0.14 || CommentsPercentage > 0.26)
		printf("Grade B: Good commmenting style.\n");
	else
		printf("Grade A: Excellent commenting style.\n");

	if (BlankPercentage < 0.05 || BlankPercentage > 0.35)
		printf("Grade D: Bad white space style.\n");
	else if (BlankPercentage < 0.09 || BlankPercentage > 0.31)
		printf("Grade C: Acceptable white space style.\n");
	else if (BlankPercentage < 0.14 || BlankPercentage > 0.26)
		printf("Grade B: Good white space style.\n");
	else
		printf("Grade A: Excellent white space style.\n");
}

int main() {
	char FileName[STRING_SIZE_MAX];
	char* Source;
	printf("Input the source file:\n");
	fgets(FileName, STRING_SIZE_MAX, stdin);
	FileName[strlen(FileName) - 1] = 0;
	if (LoadFile(FileName, &Source) == success) {
		int CodeLine, CommentLine, BlankLine, TotalLine, Function;
		double AvgFunLength;
		CountElement(Source, &CodeLine, &CommentLine, &BlankLine, &TotalLine, &Function, &AvgFunLength);
		PrintResult(FileName, CodeLine, CommentLine, BlankLine, TotalLine, Function, AvgFunLength);
	}
	else printf("Check your filename!\n");
	return 0;
}