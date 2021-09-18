
//This program deals with three linked list A, B and C.
//It deletes any node of A that has the same value with a node that exists in both B and C.
//List B and C remains untouched.

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct LNode{
	ElementType Data;
	struct LNode *Next;
};
typedef struct LNode LNode, *PtrToLNode, *List;

PtrToLNode MallocHelper(ElementType X) {
	PtrToLNode ptr = (PtrToLNode)malloc(sizeof(LNode));
	if(ptr == NULL) exit(EXIT_FAILURE);
	ptr->Data = X;
	ptr->Next = NULL;
	return ptr;
}

PtrToLNode Append(List L, PtrToLNode NewNode, PtrToLNode Last) {
/*	Append a node to the end of the list or, after Last if the last node is given.
 *  The last node of the list or the newnode itself will be returned. */
	if(Last) {
		NewNode->Next = Last->Next;
		Last->Next = NewNode;
		return NewNode;
	}
	PtrToLNode cur = L;
	while(cur) {
		if(cur->Next == NULL) break;
		cur = cur->Next;
	}
	NewNode->Next = NULL;
	cur->Next = NewNode;
	return NewNode;
}

List CreateList(List L) {
	//We create a list with a head node.
	L = MallocHelper(0);
	printf("Please input the number of nodes (1 for empty list):\n");

	size_t n;
	ElementType X;
	PtrToLNode NodeToAdd, last = L;
	scanf("%zd", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &X);
		NodeToAdd = MallocHelper(X);
		last = Append(L, NodeToAdd, last);
	}
	return L; //return L is necessary for L in the original function will not update itself
}

void PrintList(List L) {
	PtrToLNode cur = L->Next;
	while(cur) {
		printf("%d ", cur->Data);
		cur = cur->Next;
	}
	putchar('\n');
}

void solve(List A, List B, List C) {

	PtrToLNode pa = A->Next, pb = B->Next, pc = C->Next;
	PtrToLNode pre = A;
	//NULL->... is illegal, so before such operation, we have to assure the pointer is not NULL.
	while(pa && pb && pc) {
		while(pb && pc && pb->Data < pc->Data)
			pb = pb->Next;
		while(pb && pc && pc->Data < pb->Data)
			pc = pc->Next;
		if(pb && pc && pc->Data == pb->Data) {
			while(pa && pa->Data <= pb->Data) {
				if(pa->Data == pb->Data) {
					pre->Next = pa->Next;
					free(pa);
					pa = pre->Next;
					continue;
				}
				pre = pa;
				pa = pa->Next;
			}
			//These two statements are necessary, without which the program may never come to an end.
			pb = pb->Next;
			pc = pc->Next;
		}
	}
}

int main() {
	List A, B, C;
	A = CreateList(A);
	B = CreateList(B);
	C = CreateList(C);	
	PrintList(A);
	PrintList(B);
	PrintList(C);
	solve(A, B, C);
	PrintList(A);
	PrintList(B);
	PrintList(C);
	return 0;
}

