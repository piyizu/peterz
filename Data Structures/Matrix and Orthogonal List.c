#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* This program is an application of orthogonal list in
* matrix storage. I only coded for the most basic operations.
* Matrix addition and multiplication can be easily implemented
* with the help of those operations.
*/

/* Matrix stored using orthogonal list*/
/* (a(ij)), i and j start from 0!!!*/
#define TF "%d"

typedef int ElementType;
typedef struct Tuple {
	int Row, Col;
	ElementType X;
	struct Tuple* Right, * Down;
} Tuple, * PtrToTuple;
typedef struct Matrix {
	int AllRow, AllCol;
	PtrToTuple* RowList, * ColList;
} Matrix, * PtrToMatrix;

void InitMatrix(PtrToMatrix Matrix, int AllRow, int AllCol) {
	Matrix->AllRow = AllRow;
	Matrix->AllCol = AllCol;
	Matrix->RowList = (PtrToTuple*)malloc(AllRow * sizeof(PtrToTuple));
	if (Matrix->RowList == NULL) {
		exit(EXIT_FAILURE);
	}
	Matrix->ColList = (PtrToTuple*)malloc(AllCol * sizeof(PtrToTuple));
	if (Matrix->ColList == NULL) {
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < AllRow; ++i) {
		Matrix->RowList[i] = NULL;
	}
	for (int i = 0; i < AllCol; ++i) {
		Matrix->ColList[i] = NULL;
	}
}

void DestroyMatrix(PtrToMatrix Matrix) {
	if (Matrix->ColList) {
		free(Matrix->ColList);
	}
	if (Matrix->RowList) {
		for (int i = 0; i < Matrix->AllRow; ++i) { //free all element tuples
			if (Matrix->RowList[i]) {
				PtrToTuple cur = Matrix->RowList[i];
				PtrToTuple temp = NULL;
				while (cur) {
					temp = cur;
					cur = cur->Right;
					free(temp);
				}
			}
		}
		free(Matrix->RowList);
	}
	Matrix->AllCol = Matrix->AllRow = 0;
}

void AddElement(PtrToMatrix Matrix, const ElementType* PtrToEle, int Row, int Col) {
	PtrToTuple NewElement = (PtrToTuple)malloc(sizeof(Tuple));
	if (NewElement == NULL) {
		exit(EXIT_FAILURE);
	}

	NewElement->Row = Row;
	NewElement->Col = Col;
	NewElement->X = *PtrToEle;

	//Now add the item to the rowlist
	if (Matrix->RowList[Row] == NULL || Matrix->RowList[Row]->Col > Col) {
		NewElement->Right = Matrix->RowList[Row];
		Matrix->RowList[Row] = NewElement;
	}
	else {
		PtrToTuple cur = Matrix->RowList[Row];
		while (cur->Right) {
			if (cur->Col < Col && cur->Right->Col > Col) {
				break;
			}
			cur = cur->Right; /////////////////////////
		}
		NewElement->Right = cur->Right;
		cur->Right = NewElement;
	}

	//Now add the item to the collist
	if (Matrix->ColList[Col] == NULL || Matrix->ColList[Col]->Row > Row) {
		NewElement->Down = Matrix->ColList[Col];
		Matrix->ColList[Col] = NewElement;
	}
	else {
		PtrToTuple cur = Matrix->ColList[Col];
		while (cur->Down) {
			if (cur->Row < Row && cur->Down->Row > Row) {
				break;
			}
			cur = cur->Down; //////////////////////////////////
		}
		NewElement->Down = cur->Down;
		cur->Down = NewElement;
	}
}

void DeleteElement(PtrToMatrix Matrix, int Row, int Col) {
	PtrToTuple ItemBeforeInRow = Matrix->RowList[Row], ItemBeforeInCol = Matrix->ColList[Col];
	while (ItemBeforeInRow) { //look for [row, col] in rowlist
		if (ItemBeforeInRow->Right->Col == Col) break;
		ItemBeforeInRow = ItemBeforeInRow->Right;
	}

	while (ItemBeforeInCol) { //look for [row, col] in collist
		if (ItemBeforeInCol->Down->Row == Row) break;
		ItemBeforeInCol = ItemBeforeInCol->Down;
	}

	if (ItemBeforeInRow && ItemBeforeInCol) {
		PtrToTuple temp = ItemBeforeInRow->Right;
		ItemBeforeInRow->Right = temp->Right;
		ItemBeforeInCol->Down = temp->Down;
		free(temp);
	}
}

void PrintMatrix(PtrToMatrix Matrix, bool RowMode) {
	if (RowMode) {
		for (int i = 0; i < Matrix->AllRow; ++i) {
			PtrToTuple cur = Matrix->RowList[i];
			printf("Line %d: ", i);
			while (cur) {
				printf("[%d,%d]("TF") ", cur->Row, cur->Col, cur->X);
				cur = cur->Right;
			}
			printf("\n");
		}
	}
	else {
		for (int i = 0; i < Matrix->AllCol; ++i) {
			PtrToTuple cur = Matrix->ColList[i];
			printf("Column %d: ", i);
			while (cur) {
				printf("[%d,%d]("TF") ", cur->Row, cur->Col, cur->X);
				cur = cur->Down;
			}
			printf("\n");
		}
	}
}

void PrintMatrixAll(PtrToMatrix Matrix) {
	for (int i = 0; i < Matrix->AllRow; ++i) {
		PtrToTuple NonZero = Matrix->RowList[i];
		for (int j = 0; j < Matrix->AllCol; ++j) {
			if (NonZero && NonZero->Col == j) {
				printf(TF"\t", NonZero->X);
				NonZero = NonZero->Right;
			}
			else printf("0\t");
		}
		printf("\n");
	}
}

int main() {
	Matrix M;
	int temp = 0;
	InitMatrix(&M, 4, 4);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp = i * 10 + j;
			AddElement(&M, &temp, i, j);
		}
	}

	PrintMatrixAll(&M);
	DeleteElement(&M, 3, 3);
	DeleteElement(&M, 1, 1);
	DeleteElement(&M, 2, 2);
	PrintMatrixAll(&M);
	DestroyMatrix(&M);

	return 0;
}
