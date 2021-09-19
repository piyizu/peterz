#include <stdio.h>

//This program shows a simple implementation of linked list using arrays.
//You should input a list with no less than 8 nodes to test the functions.
//
#define MAXSIZE 8 //the head node is included
//MAXSIZE is also used to indicate the end of the list
#define TF "%d"

typedef int ElementType;
typedef struct LNode {
	ElementType Data;
	size_t Next;
} LNode, List;

void IniList(List *L, List *LS) {
	//L[0] is the head node of List L
	//LS[0] is the head node of List LS
	L[0].Data = 0;
	L[0].Next = MAXSIZE;
	for(int i = 1; i < MAXSIZE; ++i) {
		L[i].Data = 0;
		L[i].Next = i + 1;
	}
	LS[0].Data = 0;
	LS[0].Next = 1;
}

void InsertAfter(List *L, size_t Position, List *LS, ElementType X) {
	//if Position == MAXSIZE, the fuction will add the new node to the end of List L
	//when there are enough spare nodes in List LS.
	//otherwise, it will insert the new node after L[Postion].
	//BE CAREFUL: this function will not check whether L[Position] is in LS!!!
	if(LS[0].Next == MAXSIZE) {
		printf("ERROR! No space for the new node.\n"TF" is not in.\n", X);
		return;
	}
	if(Position > MAXSIZE) {
		printf("ERROR! Invalid position!\n"TF" is not in.\n", X);
		return;
	}
	if(Position == MAXSIZE) {
		size_t temp = 0;
		while(L[temp].Next != MAXSIZE)
			temp = L[temp].Next;
		Position = temp;
	}
	size_t temp = LS[0].Next;
	LS[0].Next = L[temp].Next;
	L[temp].Next = L[Position].Next;
	L[Position].Next = temp;
	L[temp].Data = X;
	printf("Insertion completed!\n");
}

void DeletePosition(List *L, size_t Position, List *LS) {
	if(Position >= MAXSIZE) {
		printf("ERROR! Invalid position! Deletion failed!\n");
		return;
	}
	size_t pre = 0;
	while(pre != MAXSIZE && L[pre].Next != Position) 
		pre = L[pre].Next;
	if(pre == MAXSIZE) {
		printf("ERROR! No such position in the list! Deletion failed!\n");
		return;
	}
	L[pre].Next = L[Position].Next;
	L[Position].Next = LS[0].Next;
	LS[0].Next = Position;
	printf("Deletion comlpeted!\n");
}

void PrintList(List *L) {
	//DO NOT PRINT SPARE LIST
	size_t cur = L[0].Next;
	while(cur != MAXSIZE) {
		printf(TF" ", L[cur].Data);
		cur = L[cur].Next;
	}
	printf("PRINT TO END\n");
}

int main() {
	List A[MAXSIZE], AS; //SA is the spare list of A.
	IniList(A, &AS);
	PrintList(A);
	
	size_t n;
	ElementType X;
	printf("Please input the number of nodes:");
	scanf("%zd", &n);
	printf("Input the node values:\n");
	for(int i = 1; i <= n; ++i) {
		scanf(TF, &X);
		InsertAfter(A, MAXSIZE, &AS, X);
	}
	PrintList(A);

	DeletePosition(A, 3, &AS);
	InsertAfter(A, MAXSIZE, &AS, 100);

	PrintList(A);

	DeletePosition(A, 5, &AS);
	InsertAfter(A, 4, &AS, -1);

	PrintList(A);
	return 0;
}
