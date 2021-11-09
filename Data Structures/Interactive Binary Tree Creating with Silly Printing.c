#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* This program shows how to create a binary tree using
* an interactive method and how we should print it.
* Although very simple and silly, at least it is a way to build a tree.
*/


#define PRINT_BLANK(level) for(int i = 0; i < level; ++i) printf("   ")
// above is for print blanks

typedef struct bin_tree_node {
	int index, weight;
	struct bin_tree_node* left, * right, *parent;
}bin_tree_node, * ptr_to_bin_tree_node, * bin_tree;

void create_bin_tree(bin_tree * bt, int level) {
	int index_temp;
	PRINT_BLANK(level);
	printf("Index:");
	if (scanf("%d", &index_temp) != 1) exit(EXIT_FAILURE);

	if (index_temp < 0) {
		*bt = NULL;
		return;
	}
	else {
		*bt = (bin_tree)malloc(sizeof(bin_tree_node));
		if (bt == NULL) exit(EXIT_FAILURE);

		(*bt)->index = index_temp;
		PRINT_BLANK(level);
		printf("Left Child {\n");
		create_bin_tree(&(*bt)->left, level + 1);
		PRINT_BLANK(level);
		printf("}\n");
		PRINT_BLANK(level);
		printf("Right Child {\n");
		create_bin_tree(&(*bt)->right, level + 1);
		PRINT_BLANK(level);
		printf("}\n");
	}
}

bool empty_bin_tree(bin_tree bt) {
	return bt == NULL;
}

void destroy_bin_tree(bin_tree* bt) {
	if (*bt == NULL) return;
	if ((*bt)->left == NULL && (*bt)->right == NULL) {
		free((*bt));
		(*bt) = NULL;
	}
	else {
		if ((*bt)->left) destroy_bin_tree(&(*bt)->left);
		if ((*bt)->right) destroy_bin_tree(&(*bt)->right);
	}
}

void print_bin_tree(bin_tree bt, int level) {
	if (bt == NULL) return;
	if (bt->left == NULL && bt->right == NULL) {
		PRINT_BLANK(level);
		printf("(%d)\n", bt->index);
	}
	else {
		if(bt->right) print_bin_tree(bt->right, level + 1);
		PRINT_BLANK(level);
		printf("(%d)\n", bt->index);
		if (bt->left) print_bin_tree(bt->left, level + 1);
	}

	/*for example:
	* output: 
		  (4)
	   (1)
			 (3)
		  (2)
	  is from the binary tree:
	         (1)
			/   \
		   (2)  (4)
		     \
			 (3)
	*/
}

int main() {
	bin_tree bt;
	printf("Negative index means no such node!\n");
	create_bin_tree(&bt, 1);
	print_bin_tree(bt, 1);
	destroy_bin_tree(&bt);
	return 0;
}