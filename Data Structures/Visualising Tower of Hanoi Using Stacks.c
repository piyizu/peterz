#include <stdio.h>
#include <stdlib.h>

/**
 * This program visualises the solving of problem of the tower of Hanoi.
 * Using classical recursions, the program prints the solution to ./out.txt, 
 *  which you can view afterwards.
 * The program requires you to give the number of plates after running.
 * 
 * It is another application of stacks.
*/

typedef enum PoleAttr{starting, destination, as_spare} PoleAttr;
typedef enum Status{success, failure} Status;
typedef struct Pole{
	int *PoleStack;
	int Top;
	size_t Size;
} Pole, *PtrToPole;

Pole X, Y, Z;

Status InitPole(PtrToPole P, size_t Size, PoleAttr Attr) {
	P->Top = -1; // set the stack to be empty regardless of its capacity
	P->PoleStack = (int *)malloc(Size * sizeof(int));
	if(P->PoleStack == NULL) {
		printf("Fail to Initialise the Pole!\n");
		return failure;
	}
	else {
		P->Size = Size;
		if(Attr == starting)
			for(int i = Size; i >= 1; --i)
				P->PoleStack[++P->Top] = i;
		return success;
	}
}

void DestroyPole(PtrToPole P) {
	free(P->PoleStack);
	P->Size = 0;
	P->Top = -1;
}

void PrintHanoiHelper(PtrToPole P, int LayerIndex) {
	printf("  ");
	if(P->Top < LayerIndex) {
		for(int i = 0; i < 32; ++i) {
			if(i == 15) {
				printf("**");
				++i;
			}
			else putchar(' ');
		}
	}
	else {
		int start = 16 - P->PoleStack[LayerIndex];
		int end = 31 - start;
		for(int i = 0; i < 32; ++i) {
			if(i >= start && i <= end) {
				printf("[]");
				++i;
			}
			else putchar(' ');
		}
	}
	printf("  ");
}

void PrintHanoi() {
	for(int i = X.Size - 1; i >= 0; --i) {
		PrintHanoiHelper(&X, i);
		PrintHanoiHelper(&Y, i);
		PrintHanoiHelper(&Z, i);
		putchar('\n');
	}
	putchar('\n');
}

void VisualHanoi(int BottomNumber, PtrToPole StartingPole, PtrToPole DestPole, PtrToPole SparePole) {
	if(BottomNumber == 1) {
		DestPole->PoleStack[++DestPole->Top] = StartingPole->PoleStack[StartingPole->Top--];
		PrintHanoi();
	}
	else {
		VisualHanoi(BottomNumber - 1, StartingPole, SparePole, DestPole);
		DestPole->PoleStack[++DestPole->Top] = StartingPole->PoleStack[StartingPole->Top--];
		PrintHanoi();
		VisualHanoi(BottomNumber - 1, SparePole, DestPole, StartingPole);
	}
}

int main() {
	freopen("./out.txt", "w", stdout);
	int i; 
	scanf("%d", &i); // How many plates?
	InitPole(&X, i, starting);
	InitPole(&Y, i, as_spare);
	InitPole(&Z, i, destination);
	PrintHanoi();
	VisualHanoi(i, &X, &Z, &Y);
	DestroyPole(&Z);
	DestroyPole(&Y);
	DestroyPole(&X);
	return 0;
}
