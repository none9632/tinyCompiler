#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

// kind list
enum
{
	K_ADD,
	K_SUB,
	K_MULT,
	K_DIV,
	K_NUM,
	K_NONE
};

typedef struct node
{
	int kind;
	int value;
	struct node *n1;
	struct node *n2;
}
Node;

Node *new_node   ();
void  start_print_node(Node *n);

#endif