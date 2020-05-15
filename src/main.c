#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/node.h"

static int   help      = 0;
static int   print_ast = 0;
static char *expr      = NULL;

static void usage(int exit_status)
{
	printf("Usage: tinyCompiler [options] <expression>\n");
	printf("\nOptions:\n");
	printf("    -h              display this information\n");
	printf("    -print-ast      display AST\n");
	printf("\n");
	exit(exit_status);
}

static void parse_options(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		char *opt = argv[i];

		if (*opt == '-')
		{
			if (!strcmp(opt, "--help"))
				help = 1;
			else if (!strcmp(opt, "--print-ast"))
				print_ast = 1;
			else
			{
				printf("error: invalid option\n");
				usage(1);
			}
		}
		else
		{
			if (expr == NULL)
				expr = opt;
			else
			{
				printf("error: invalid input\n");
				usage(1);
			}
		}
	}
}

int main(int argc, char **argv)
{
	parse_options(argc, argv);

	if (expr == NULL)
	{
		printf("error: No input expression\n");
		usage(1);
	}

	if (help == 1)
		usage(0);

	init_lexer(expr);
	Node *n = parser();

	if (print_ast == 1)
		output_node(n, 0);
}
