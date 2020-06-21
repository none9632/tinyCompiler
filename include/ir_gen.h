#ifndef IR_GEN_H
#define IR_GEN_H

#include <malloc.h>

#include "node.h"
#include "error.h"
#include "vector.h"

enum
{
	C_LOAD,
	C_ADD,
	C_SUB,
	C_MUL,
	C_DIV,
};

typedef struct ir
{
	int command;
	int reg1;
	int reg2;
}
IR;

Vector* start_ir_gen(Node *n, int print_ir);

#endif