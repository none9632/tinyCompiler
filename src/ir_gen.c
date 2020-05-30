#include "../include/ir_gen.h"

static Vector *ir_code;

static ir_t* new_ir(int command, int reg1, int reg2)
{
	ir_t* ir = malloc(sizeof(ir_t));
	ir->command = command;
	ir->reg1 = reg1;
	ir->reg2 = reg2;
	return ir;
}

static int is_arithmetic_op(int kind)
{
	return ((kind == K_ADD) || (kind == K_SUB) || (kind == K_MULT) || (kind == K_DIV));
}

static void arithmetic_op_gen(int kind, int reg1, int reg2)
{
	ir_t *ir;

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
		ir_gen(n->n1, result_reg);
		ir_gen(n->n2, result_reg + 1);
		arithmetic_op_gen(n->kind, result_reg, result_reg + 1);
	}
	else
	{
		ir_t *ir = new_ir(C_LOAD, result_reg, n->value);

		vec_push(ir_code, ir);
	}

}

Vector* start_ir_gen(Node *n, int print_ir)
{
	ir_code = new_vec();

	ir_gen(n, 0);

	if (print_ir)
	{
		for (int i = 0; i < ir_code->length; ++i)
		{
			ir_t *ir = ir_code->data[i];

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

	return ir_code;
}