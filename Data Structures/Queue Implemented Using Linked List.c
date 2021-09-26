#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TF "%d"

/**
 * This program shows a queue implemented by linked list and its simple applications.
 * Most common functions have been built.
 * All is done with the help of our textbook --- Data Structures by Weimin Yan
*/

typedef int ElementType;
typedef struct QueueNode{
	ElementType X;
	struct QueueNode * Next;
} QueueNode, *PtrToQueueNode;
typedef struct Queue{
	PtrToQueueNode Front;
	PtrToQueueNode Rear;
} Queue, *LinkedQueue, *PtrToQueue;
typedef enum status{success, failure} status;

PtrToQueueNode MallocHelper(ElementType X) {
	PtrToQueueNode ptr = (PtrToQueueNode)malloc(sizeof(QueueNode));
	if(ptr == NULL) {
		printf("MallocHelper(): Fail to get memory space!\n");
		return NULL;
	}
	else {
		ptr->X = X;
		ptr->Next = NULL;
		return ptr;
	}
}

status InitQueue(LinkedQueue Q) {
	Q->Front = MallocHelper(0);
	if(Q->Front == NULL) {
		printf("InitQueue(): Fail to get memory space!\n");
		return failure;
	}
	else {
		Q->Rear = Q->Front;
		return success;
	}
}

void DestroyQueue(LinkedQueue Q) {
	while(Q->Front->Next) {
		PtrToQueueNode temp = Q->Front->Next;
		Q->Front->Next = temp->Next;
		free(temp);
	}
	Q->Rear = NULL;
	free(Q->Front);
	Q->Front = NULL;
}

bool QueueIsEmpty(LinkedQueue Q) {
	return Q->Front == Q->Rear;
}

status EnQueue(LinkedQueue Q, ElementType X) {
	Q->Rear->Next = MallocHelper(X);
	if(Q->Rear->Next == NULL) {
		printf("EnQueue(): Fail to get memory space!\n");
		return failure;
	}
	else {
		Q->Rear = Q->Rear->Next;
		return success;
	}
}

status DeQueue(LinkedQueue Q, ElementType *X) {
	if(Q->Front->Next) {
		*X = Q->Front->Next->X;
		PtrToQueueNode temp = Q->Front->Next;
		Q->Front->Next = temp->Next;
		free(temp);
		if(Q->Front->Next == NULL)
		// After deleting the last node in queue, the rear pointer should be reset.
			Q->Rear = Q->Front;
		return success;
	}
	else {
		printf("DeQueue(): Empty queue!\n");
		return failure;
	}
}

status GetFront(LinkedQueue Q, ElementType *X) {
	if(Q->Front->Next) {
		*X = Q->Front->Next->X;
		return success;
	}
	else {
		printf("GetFront(): Empty queue!\n");
		return failure;
	}
}

status QueueTraverse(LinkedQueue Q) {
	if(Q->Front->Next) {
		PtrToQueueNode cur = Q->Front->Next;
		while(cur) {
			printf(TF" ", cur->X);
			cur = cur->Next;
		}
		printf("DONE!\n");
		return success;
	}
	else {
		printf("QueueTraverse(): Empty queue!\n");
		return failure;
	}
}

int main() {
	LinkedQueue Q;

	/* Q is just a pointer and is set to point at nothing at the beginning.
		However, using gcc compiler, we get a program that runs very well.
		Is it possible that the compiler ignores Q and directly uses its member:
		Front and Rear, which are both pointers?
	*/


	InitQueue(Q);
	printf(QueueIsEmpty(Q) ? "Empty Queue!\n" : "The queue is not empty!\n");
	for(int i = 1; i < 30; i += 2) {
		EnQueue(Q, i);
		QueueTraverse(Q);
	}
	for(int i = 1; i <= 16; ++i) {
		ElementType temp;
		DeQueue(Q, &temp);
		printf(TF" ", temp);
		GetFront(Q, &temp);
		printf(TF" ", temp);
		QueueTraverse(Q);
	}
	DestroyQueue(Q);
	printf(QueueIsEmpty(Q) ? "Empty Queue!\n" : "The queue is not empty!\n");
	return 0;
}
