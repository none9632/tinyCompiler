#include "../include/ir_gen.h"

static Vector *ir_code;

static IR* new_ir(int command, int reg1, int reg2)
{
	IR* ir = malloc(sizeof(IR));

	if (ir == NULL)
		error("memory allocation error in new_ir()");

	ir->command = command;
	ir->reg1    = reg1;
	ir->reg2    = reg2;

	return ir;
}

static int is_arithmetic_op(int kind)
{
	return ((kind == K_ADD) || (kind == K_SUB) || (kind == K_MULT) || (kind == K_DIV));
}

static void arithmetic_op_gen(int kind, int reg1, int reg2)
{
	IR *ir;

	switch (kind)
	{
		case K_ADD:
			ir = new_ir(C_ADD, reg1, reg2);
			break;
		case K_SUB:
			ir = new_ir(C_SUB, reg1, reg2);
			break;
		case K_MULT:
			ir = new_ir(C_MUL, reg1, reg2);
			break;
		case K_DIV:
			ir = new_ir(C_DIV, reg1, reg2);
			break;
		default:
			error("wrong operation");
			break;
	}

	vec_push(ir_code, ir);
}

static void ir_gen(Node *n, int result_reg)
{
	if (is_arithmetic_op(n->kind))
	{
		ir_gen(n->lhs, result_reg);
		ir_gen(n->rhs, result_reg + 1);
		arithmetic_op_gen(n->kind, result_reg, result_reg + 1);
	}
	else
	{
		IR *ir = new_ir(C_LOAD, result_reg, n->value);
		vec_push(ir_code, ir);
	}

}

static void print_ir()
{
	for (int i = 0; i < ir_code->length; ++i)
	{
		IR *ir = ir_code->data[i];

		switch (ir->command)
		{
			case C_LOAD: printf("LOAD R%i %i\n", ir->reg1, ir->reg2); break;
			case C_ADD:  printf("ADD R%i R%i\n", ir->reg1, ir->reg2); break;
			case C_SUB:  printf("SUB R%i R%i\n", ir->reg1, ir->reg2); break;
			case C_MUL:  printf("MUL R%i R%i\n", ir->reg1, ir->reg2); break;
			case C_DIV:  printf("DIV R%i R%i\n", ir->reg1, ir->reg2); break;
		}
	}
}

Vector* start_ir_gen(Node *n, int print_ir_flag)
{
	ir_code = new_vec();

	ir_gen(n, 0);

	if (print_ir_flag)
		print_ir();

	return ir_code;
}