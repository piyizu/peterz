#include <stdio.h>
#include <stdlib.h>

/**
 * This program implements polynomial addition and multiplication.
 * You are required to give two polynomials and the format of each input should be:
 * (How many items?) (Coefficient of Item1) (Exponent of Item1) ...
 * Each '(...)' means one integral.
 * And the result is:
 * First line: Multiplication, (Coefficient of Item1) (Exponent of Item1) ....
 * Second line: Addition. ....
 * The Add() function in this program ascertains that
 *  no two items with the same exponent will be stored.
 * The PrintPoly() function assures that items whose coefficient is 0 will not be shown.
 */

typedef struct Item {
	int A;
	int E;
	struct Item *Next;
} Item, *PtrToItem, *Polynomial;

/**
 * function declarations
*/
PtrToItem MallocHelper(int A, int E);
Polynomial CreatePoly(Polynomial P);
Polynomial Add(Polynomial A, Polynomial B);
void PrintPoly(Polynomial P);
void Delete(Polynomial P);
Polynomial MultiplyHelper(Polynomial P, int A, int E);
Polynomial Multiply(Polynomial A, Polynomial B);

PtrToItem MallocHelper(int A, int E) {
	PtrToItem ptr = (PtrToItem)malloc(sizeof(Item));
	if(ptr == NULL) exit(EXIT_FAILURE);

	ptr->A = A;
	ptr->E = E;
	ptr->Next = NULL;

	return ptr;
}

Polynomial CreatePoly(Polynomial P) {
	P = MallocHelper(0, -1);
	int n;
	scanf("%d", &n);
	if(n <= 0) return P;

	int a, e;
	PtrToItem cur = P;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a, &e);
		cur->Next = MallocHelper(a, e);
		cur = cur->Next;
	}
	
	return P;
}

Polynomial Add(Polynomial A, Polynomial B) {
	Polynomial R = MallocHelper(0, -1);
	PtrToItem pa = A->Next, pb = B->Next, pc = R;
	while(pa && pb) {
		/*Don't use three if(...){...}s here, for pc, pa and pb may be updated
			and more than one will be executed, which may results in NULL->..., a disastrous operation.
		*/
		if(pa->E > pb->E) {
			pc->Next = MallocHelper(pa->A, pa->E);
			pc = pc->Next;
			pa = pa->Next;
		}
		else if(pa->E == pb->E) {
			pc->Next = MallocHelper(pa->A + pb->A, pa->E);
			pc = pc->Next;
			pa = pa->Next;
			pb = pb->Next;
		}
		else{
			pc->Next = MallocHelper(pb->A, pb->E);
			pc = pc->Next;
			pb = pb->Next;
		}
	}
	while(pa) {
		pc->Next = MallocHelper(pa->A, pa->E);
		pc = pc->Next;
		pa = pa->Next;
	}
	while(pb) {
		pc->Next = MallocHelper(pb->A, pb->E);
		pc = pc->Next;
		pb = pb->Next;
	}
	return R;
}

void PrintPoly(Polynomial P) {
	PtrToItem cur = P->Next;
	int no00flag = 0;
	int firstoutflag = 1;
	while(cur) {
		if(cur->A) {
			firstoutflag ? (firstoutflag = 0) : putchar(' ');
			printf("%d %d", cur->A, cur->E);
			no00flag = 1;
		}
		cur = cur->Next;
	}
	if(!no00flag) printf("0 0");
}

Polynomial MultiplyHelper(Polynomial P, int A, int E) {
	Polynomial R = MallocHelper(0, -1);
	PtrToItem pr = R, pp = P->Next;
	while(pp) {
		pr->Next = MallocHelper(pp->A * A, pp->E + E);
		pr = pr->Next;
		pp = pp->Next;
	}
	return R;
}

Polynomial Multiply(Polynomial A, Polynomial B) {
	Polynomial temp1 = NULL, temp2 = NULL, R = NULL;
	PtrToItem pb = B->Next;
	while(pb) {
		temp1 = MultiplyHelper(A, pb->A, pb->E);
		if(R == NULL)
			R = temp1;
		else {
			temp2 = Add(temp1, R);
			Delete(temp1);
			Delete(R);
			R = temp2;
		}
		pb = pb->Next;
	}
	return R ? R : MallocHelper(0, -1);
}

void Delete(Polynomial P) {
	PtrToItem cur = P, temp;
	while(cur) {
		temp = cur;
		cur = cur->Next;
		free(temp);
	}
}

int main() {
	Polynomial PA, PB, PC, PD;
	PA = CreatePoly(PA);
	PB = CreatePoly(PB);
	PC = Add(PA, PB);
	PD = Multiply(PA, PB);
	PrintPoly(PD);
	putchar('\n');
	PrintPoly(PC);
	Delete(PA);
	Delete(PB);
	Delete(PC);
	return 0;
}
