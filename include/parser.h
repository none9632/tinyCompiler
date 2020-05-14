#ifndef PARSER_H
#define PARSER_H

#include "../include/lexer.h"
#include "../include/error.h"

typedef struct node
{
	int kind;
	int value;
	struct node *n1;
	struct node *n2;
}
		Node;

Node* parser();

#endif