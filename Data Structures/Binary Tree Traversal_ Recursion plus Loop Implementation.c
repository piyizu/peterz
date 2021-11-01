#include <stdio.h>
#include <stdlib.h>

/* We are given a binary tree which is built in an unknown way.
	Our task is to traverse the whole tree in pre-order,
	in-order, post-order and level-order.
	The following imcomplete code shows how we should complete
	that task.
	We give both the recursion and non-recursion implementations
	for pre-order, in-order and post-order traversal.
*/

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* We don't care how this works */
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}

/*void PreorderTraversal(BinTree BT) {
    if(BT == NULL) return;
    else {
        printf(" %c", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
*/
void PreorderTraversal(BinTree BT) {
    if(BT == NULL) return; // Empty tree test
    Position* S = (Position *)malloc(1024 * sizeof(Position)); //The size of the stack is 1024!
    if(S == NULL) exit(EXIT_FAILURE); //memory allocation test
    *S = BT;
    int Top = 0;
    Position P;
    while(Top != -1 && (P = S[Top]) ) {
    	//At this point, the top node of the stack is yet not visited.
        printf(" %c", P->Data);
        if(P->Left) S[++Top] = P->Left;
        else {
        	// If we got here, all nodes in the stack would be visited.
            while(Top != -1 && (P = S[Top]) ) {
                --Top;
                if(P->Right) { // Go to the next right subtree to visit.
                    S[++Top] = P->Right;
                    break;
                }
            }
        }
    }
    free(S);
}

/*void InorderTraversal(BinTree BT) {
    if(BT == NULL) return;
    else {
        InorderTraversal(BT->Left);
        printf(" %c", BT->Data);
        InorderTraversal(BT->Right);
    }
}*/
void InorderTraversal(BinTree BT) {
    if(BT == NULL) return;
    Position *S = (Position *)malloc(1024 * sizeof(Position));
    if(S == NULL) exit(EXIT_FAILURE);
    *S = BT;
    int Top = 0;
    Position P;
    while(Top != -1) {
        P = S[Top];
        // At this point, no tree node in the stack is visited.
        if(P->Left)
            S[++Top] = P->Left; // push the left subtree into the stack first
        else {
            while(Top != -1) {
            // no left subtree or left subtree has been visited? visit the current node and pop it!
                P = S[Top];
                printf(" %c", P->Data);
                --Top;
                if(P->Right) { 
				//if we find a right subtree to visit, we should visit it first
                    S[++Top] = P->Right;
                    break;
                }
            }
        }
    }
    free(S);
}

/*
void PostorderTraversal(BinTree BT) {
    if(BT == NULL) return;
    else {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf(" %c", BT->Data);
    }
}
*/
void PostorderTraversal(BinTree BT) {
    if(BT == NULL) return;
    Position *S = (Position *)malloc(1024 * sizeof(Position));
    if(S == NULL) exit(EXIT_FAILURE);
    *S = BT;
    int Top = 0;
    Position P;
    while(Top != -1) {
    	//At this point, the top node and its two subtrees are not visited.
        P = S[Top];
        if(P->Left == NULL && P->Right == NULL) {
            printf(" %c", P->Data);
            --Top;
            while(Top != -1) {
            	//If we got here, no node in the stack would be visited.
                P = S[Top];
                if(P == NULL) { //NULL flag indicates that we return from the left subtree.
                    --Top;
                    P = S[Top];
                    if(P->Right) { // Push the next right subtree to visit into the stack
                        S[++Top] = P->Right;
                        break;
                    }
                }
                printf(" %c", P->Data);
                --Top;
            }
        }
        else {
        	// push the subtrees of the top node into the stack.
            if(P->Left) {
                S[++Top] = NULL; // left subtree returning flag
                S[++Top] = P->Left;
            }
            else {
                S[++Top] = P->Right;
            }
        }
    }
    free(S);
}

void LevelorderTraversal(BinTree BT) {
    if(BT == NULL) return;
    else {
        Position* Queue = (Position *)malloc(10240 * sizeof(Position));
        Queue[0] = BT;
        Position Cur;
        int Head = 0, Tail = 1;
        while(Head < Tail) {
            Cur = Queue[Head++];
            printf(" %c", Cur->Data);
            if(Cur->Left) Queue[Tail++] = Cur->Left;
            if(Cur->Right) Queue[Tail++] = Cur->Right;
        }   
    }
}
