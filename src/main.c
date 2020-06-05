#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/node.h"
#include "../include/ir_gen.h"
#include "../include/asm_gen.h"

static int   help      = 0;
static int   print_ast = 0;
static int   print_ir  = 0;
static char *expr      = NULL;

static void usage()
{
	printf("Usage: tinyCompiler [options] <expression>\n");
	printf("\nOptions:\n");
	printf("    --help          display this information\n");
	printf("    --print-ast     display AST\n");
	printf("    --print-ir      display intermediate representation of the code\n");
	printf("\n");
	exit(EXIT_SUCCESS);
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
			else if (!strcmp(opt, "--print-ir"))
				print_ir = 1;
			else
			{
				printf("error: invalid option\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (expr == NULL)
				expr = opt;
			else
			{
				printf("error: invalid input\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int main(int argc, char **argv)
{
	parse_options(argc, argv);

	if (help == 1)
		usage(0);

	if (expr == NULL)
	{
		printf("error: No input expression\n");
		exit(EXIT_FAILURE);
	}

	init_lexer(expr);
	Node *n = parser();

	if (print_ast == 1)
		output_node(n, 0);

	Vector *ir_code = start_ir_gen(n, print_ir);
	code_gen(ir_code);
}
