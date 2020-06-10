#include "../include/node.h"

Node* new_node()
{
	Node *n = malloc(sizeof(Node));
	n->kind = K_NONE;
	n->value = 0;
	n->n1 = NULL;
	n->n2 = NULL;
	return n;
}

static void print_kind(int kind, int value)
{
	switch (kind)
	{
		case K_ADD:  printf("+\n");         break;
		case K_SUB:  printf("-\n");         break;
		case K_MULT: printf("*\n");         break;
		case K_DIV:  printf("/\n");         break;
		case K_NUM:  printf("%i\n", value); break;
		case K_NONE: printf("none\n");      break;
	}
}

/*
 * The '│' symbol cannot be saved to the pointer so I save '|' and output '│'.
 */
static void print_prefix(char *prefix, int prefix_len)
{
	for (int i = 0; i < prefix_len; i++)
	{
		if (prefix[i] == '|')
			printf("│");
		else
			printf("%c", prefix[i]);
	}
}

/*
 * Adds '|   ' or '    ' to the prefix.
 */
static char *new_prefix(char *prefix, int prefix_len, int is_left)
{
	prefix = realloc(prefix, prefix_len + 4);

	for (int i = prefix_len; i < prefix_len + 4; ++i)
		prefix[i] = ' ';

	if (is_left)
		prefix[prefix_len] = '|';

	return prefix;
}

void print_node(Node *n, char *prefix, int prefix_len, int is_left)
{
	if (n != NULL)
	{
		print_prefix(prefix, prefix_len);

		printf("%s", (is_left ? "├── " : "└── "));

		print_kind(n->kind, n->value);

		prefix = new_prefix(prefix, prefix_len, is_left);
		prefix_len += 4;

		print_node(n->n1, prefix, prefix_len, 1);
		print_node(n->n2, prefix, prefix_len, 0);
	}
}

void start_print_node(Node *n)
{
	print_kind(n->kind, n->value);

	print_node(n->n1, NULL, 0, 1);
	print_node(n->n2, NULL, 0, 0);
}
