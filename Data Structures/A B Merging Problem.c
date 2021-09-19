#include <stdio.h>
#include <stdlib.h>

//Given non-decreasing linked list A and B, merge the lists to a new list C.
//Leaving A and B unchanged is NOT necessary.
//
#define TF "%d"

typedef int ElementType;
typedef struct LNode {
	ElementType Data;
	struct LNode * Next;
} LNode, *List, *PtrToLNode;

PtrToLNode MallocHelper(ElementType X) {
	PtrToLNode ptr = (PtrToLNode)malloc(sizeof(LNode));
	if(ptr == NULL) exit(EXIT_FAILURE);
	ptr->Data = X;
	ptr->Next = NULL;
	return ptr;
}

List CreateList(List L) {
	L = MallocHelper(0);

	size_t n;
	PtrToLNode cur = L;
	ElementType X;

	printf("The number of nodes:");
	scanf("%zd", &n);
	
	printf("Please input the Data value of each node:\n");
	for(int i = 1; i <= n; ++i) {
		scanf(TF, &X);
		cur->Next = MallocHelper(X);
		cur = cur->Next;
	}
	
	return L;
}

List MergeList(List A, List B) {
	// A and B will be rendered useless. DO NOT USE them after calling this function.
	List C = MallocHelper(0);

	PtrToLNode pa = A->Next, pb = B->Next, pcCur = C;
	while(pa && pb) {
		if(pa->Data <= pb->Data) {
			pcCur->Next = pa;
			pa = pa->Next;
			pcCur = pcCur->Next;
		}
		else {
			pcCur->Next = pb;
			pb = pb->Next;
			pcCur = pcCur->Next;
		}
	}
	//As A and B are all linked list, just linked the next node not merged
	// and do nothing for the rest nodes.
	if(pa) pcCur->Next = pa;
	else pcCur->Next = pb;

	free(A);
	free(B);

	return C;
}

void PrintList(List L) {
	PtrToLNode cur = L->Next;
	while(cur) {
		printf(TF" ", cur->Data);
		cur = cur->Next;
	}
	printf("PRINT TO END\n");
}

int main() {
	List A, B, C;
	A = CreateList(A);
	B = CreateList(B);
	PrintList(A);
	PrintList(B);
	C = MergeList(A, B);
	PrintList(C);
	return 0;
}
