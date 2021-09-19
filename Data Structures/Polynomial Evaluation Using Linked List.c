#include <stdio.h>
#include <stdlib.h>

// The storage and evaluation of polynomial.
// This program uses a linked list to store the polynomial.
// It applies an O(n) algorithm to evaluate the polynomial at x = x0 given by the user.

typedef struct Item{
	double A;
	int E;
	struct Item * Next;
}  Item, *Polynomial, *PtrToItem;

PtrToItem MallocHelper(Item X) {
	PtrToItem ptr = (PtrToItem)malloc(sizeof(Item));
	if(ptr == NULL) exit(EXIT_FAILURE);

	ptr->A = X.A;
	ptr->E = X.E;
	ptr->Next = NULL;
	return ptr;
}

Polynomial CreatePoly(Polynomial P) {
	printf("We are going to build a list for your polynomial.\n");
	printf("Input a*x^n as this: n a<ENTER>. If there is no more item, just input -1.\n");
	Item newitem;
	
	newitem.A = 0;
	newitem.E = -1;
	newitem.Next = NULL;
	P = MallocHelper(newitem);

	while( scanf("%d", &newitem.E) == 1 && newitem.E >= 0) {
		scanf("%lf", &newitem.A);
		PtrToItem NewItem = MallocHelper(newitem);
		PtrToItem cur = P;
		while(cur) { //Add the current item to the list and make the list non-increasing in item exponent.
			if(cur->E == NewItem->E) { //This assures there will never be two items with the same exponent.
				cur->A += NewItem->A;
				free(NewItem);
				break;
			}
			if(!cur->Next || cur->Next->E < NewItem->E) {
				NewItem->Next = cur->Next;
				cur->Next = NewItem;
				break;
			}
			cur = cur->Next;
		}
	}

	printf("Storage completed. The polynomial is automatically transformed to:\n");
	//Actually you rid the A=0 items from the polynomial list. Here we skip such operation.
	
	PtrToItem cur = P->Next;
	while(cur) {
		printf("%+.3lf*x^(%d)", cur->A, cur->E);
		cur = cur->Next;
	}
	putchar('\n');

	return P;

}

double Evaluate(Polynomial P, double x) {
	double val = 0.0;
	if(P->Next) {
		int emax = P->Next->E;
		PtrToItem cur = P->Next;
		for(int e = emax; e>= 0; --e) {
			if(cur && cur->E == e) {
				val = val * x + cur->A;
				cur = cur->Next;
			}
			else val = val * x;
		}
	}
	return val;
}

int main() {
	Polynomial P;
	P = CreatePoly(P);
	printf("Please input an x:");
	double x;
	scanf("%lf", &x);
	printf("The polynomial is evaluated to %.3lf at %.3lf\n", Evaluate(P, x), x);

	return 0;
}
