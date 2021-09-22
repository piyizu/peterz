#include <stdio.h>
#include <stdlib.h>
//
//This program uses a linked list to implement a stack
//The linked list contains a head node, which is actually not necessary :->
//You should initialise a stack before using it and delete it when it
//	is no longer needed.
//All tests are not carried out. But I think it should work well.
//


#define TF "%d"
typedef int ElementType;
typedef struct Item{
	ElementType X;
	struct Item * Next;
} Item, *ItemList, *PtrToItem;
typedef struct Stack{
	ItemList L;
	size_t Size;
} Stack;

PtrToItem MallocHelper(ElementType X) {
	PtrToItem ptr = (PtrToItem)malloc(sizeof(Item));
	if(ptr == NULL) exit(EXIT_FAILURE);
	ptr->X = X;
	ptr->Next = NULL;
	return ptr;
}

void StackIni(Stack *S) {
	S->L = MallocHelper(0);
	S->Size = 0;
	printf("Stack Initialised\n");
}

void StackDelete(Stack *S) {
	PtrToItem temp, cur = S->L;
	while(cur) {
		temp = cur;
		cur = cur->Next;
		free(temp);
	}
	S->L = NULL;
	S->Size = 0;
	printf("Stack Deleted\n");
}

ElementType StackPop(Stack *S) {
	if(S->L->Next == NULL) {
		printf("Empty Stack!\n");
		return 0;
	}

	ElementType re = S->L->Next->X;
	PtrToItem temp = S->L->Next;
	S->L->Next = temp->Next;
	free(temp);
	--S->Size;
	return re;
}

void StackPush(Stack *S, ElementType X) {
	PtrToItem temp = MallocHelper(X);
	temp->Next = S->L->Next;
	S->L->Next = temp;
	++S->Size;
}

int StackEmpty(Stack S) {
	return S.Size ? 0 : 1;
}

ElementType StackTop(Stack S) {
	if(S.L->Next == NULL) {
		printf("Empty Stack!\n");
		return 0;
	}
	return S.L->Next->X;
}

int main() {
	Stack S;
	StackIni(&S);
	printf("Please input how many numbers are there:\n");
	int n;
	scanf("%d", &n);
	printf(TF"\n", StackPop(&S));
	printf(TF"\n", StackTop(S));
	printf("%d\n", StackEmpty(S));
	printf("Please input the numbers:\n");
	for(; n > 0; --n) {
		ElementType X;
		scanf(TF, &X);
		StackPush(&S, X);
	}
	while(!StackEmpty(S)) {
		printf(TF" "TF"\n", StackTop(S), StackPop(&S));
	}
	StackDelete(&S);
	return 0;
}
