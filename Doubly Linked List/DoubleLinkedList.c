/*
 ============================================================================
 Name        : DoubleLinkedList.c
 Author      : Hugo Pakula
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node *back;
    int x;
    char y[50];
    struct node *next;
} node;

struct node_head {
	struct node *last;
    int cnt;
    struct node *first;
} node_head;

void printChain(node* first);
void destroyNode(char data[50], node* firstNode);
struct node* searchList(char needle[50], node* firstNode);
int menu(int forceOption);
void menu_addData();


int main(void) {
	menu(6);
	return EXIT_SUCCESS;

	printChain(node_head.first);

	//searchList("Hugo", node_head.first);
	struct node *loc = searchList("Hugo", node_head.first);
	if(loc == 0) {
		printf("Hugo NOT FOUND");
	} else {
		printf("Hugo FOUND at: ");
		printf("%i", loc->x);
	}


	return EXIT_SUCCESS;
}

int menu(int forceOption) {
	if(forceOption == 0) {
		return 0;
	} else if(forceOption == 1) {
		printf("Enter \".\" at any time to exit data entry.\n\n");
		menu_addData();
	} else if(forceOption == 2) {
		// Sort the list
	} else if(forceOption == 3) {
		printf("Enter a value to search for: ");

	} else if(forceOption == 4) {
		if(node_head.first == NULL) {
			printf("Could not run 'delete' - no data in list.\n");
		} else {
			char yval[50];
			printf("Enter a Y value to remove the first occurrence of: ");
			scanf("%s", &yval);
			destroyNode(yval, node_head.first);
		}
	} else if(forceOption == 5) {
		printChain(node_head.first);
	} else if(forceOption != 6) {
		printf("Invalid menu option.\n");
	}
	printf("Enter 0 to exit, 1 to add data, 2 to sort, 3 to search, 4 to delete, 5 to print: ");
	int response;
	scanf("%i", &response);
	printf("Menu Choice: %i\n\n", response);
	return menu(response);
}

void menu_addData() {
	char input[50];
	node_head.first = NULL;
	node_head.last = NULL;
	struct node *current = node_head.first;
	node_head.cnt = 0;
	struct node *tmp_n;

	while(strcmp(input, ".") != 0) {
		current = node_head.first;
		tmp_n = (struct node*) malloc(sizeof(struct node));
		tmp_n->next = NULL;
		tmp_n->x = node_head.cnt;
		printf("Enter a value for Y: ");
		scanf("%s", &input);
		strcpy(tmp_n->y, input);

		if(strcmp(input, ".") == 0) {
			break;
		}

		if(node_head.first == NULL) {
			node_head.first = tmp_n;
			node_head.first->back = NULL;
			node_head.cnt++;
		} else {
			while(current->next != NULL) {
				current = current->next;
			}
			tmp_n->back = current;
			current->next = tmp_n;
			node_head.cnt++;

		}
	}
}

void insertAfter(node* beforeNode) {
	if(beforeNode == NULL) {
		printf("Node does not exist in list.");
	}

	struct node *tmp_ptr;
	tmp_ptr = (struct node*) malloc(sizeof(struct node));
	if(beforeNode->next == NULL) { //End of list; malloc
		tmp_ptr->back = beforeNode;
		tmp_ptr->next = NULL;
		tmp_ptr->x = node_head.cnt;

		printf("Enter a value for Y: ");
		scanf("%s", &tmp_ptr->y);

		beforeNode->next = tmp_ptr;
	} else { //Not end of list; Swap prev/next pointers at malloc
		tmp_ptr->back = beforeNode;
		tmp_ptr->next = beforeNode->next;
		tmp_ptr->x = node_head.cnt;
		printf("Enter a value for Y: ");
		scanf("%s", &tmp_ptr->y);

		beforeNode->next = tmp_ptr;
	}
}

void insertBefore(node* afterNode) {
	insertAfter(afterNode->back);
}

void destroyNode(char data[50], node* firstNode) {
	struct node* nodeAddr = searchList(data, firstNode);
	if(nodeAddr != NULL) {
		if(nodeAddr->next == NULL) {
			nodeAddr->back->next = NULL;
		} else {
			nodeAddr->back->next = nodeAddr->next;
		}
	}
}

int sortList(node* firstNode) {
	return 0;
}

struct node* searchList(char needle[50], node* firstNode) {
	struct node *currentNode = firstNode;

	while(strcmp(currentNode->y, needle) != 0) {
		if(currentNode->next == NULL) {
			return NULL;
		}
		currentNode = currentNode->next;
	}
	return currentNode;
}

void printChain(node* first) {
	if(first == NULL) {
		printf("Chain is empty");
	}

	struct node *currentPtr = first;
	do {
		if(currentPtr->back != NULL) {
			printf("<Y<Y<Y<Y<Y<Y<Y<Y<Y<Y<Y<Y<Y: %s\n", currentPtr->back->y);
			printf("<X<X<X<X<X<X<X<X<X<X<X<X<X: %i\n", currentPtr->back->x);
		} else {
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<: NULL\n");
		}
		printf("X is: %i\n", currentPtr->x);
		printf("Y is: %s\n", currentPtr->y);
		if(currentPtr->next != NULL) {
			printf(">Y>Y>Y>Y>Y>Y>Y>Y>Y>Y>Y>Y>Y: %s\n\n", currentPtr->next->y);
		} else {
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>: NULL\n\n");
		}

		currentPtr = currentPtr->next;
	} while(currentPtr != NULL);
}

