#include "../include/asm_gen.h"

static int   count_R = -1;
static FILE *file;

static void init_data_section()
{
	fprintf(file, "section .data\n");
	fprintf(file, "\tformat db \"%%i\", 10, 0\n");

	for (int i = 0; i <= count_R; ++i)
		fprintf(file, "\tR%i dd 0d\n", i);

	fprintf(file, "\n");
}

static void init_text_section()
{
	fprintf(file, "section .text\n");
	fprintf(file, "global main\n");
	fprintf(file, "extern printf\n");
	fprintf(file, "\n");
}

static void start_program()
{
	fprintf(file, "main:\n");
	fprintf(file, "\tsub rsp, 8\n");
}

static void end_program()
{
	fprintf(file, "\n");
	fprintf(file, "\tmov esi, DWORD [R0]\n");
	fprintf(file, "\tlea rdi, [rel format]\n");
	fprintf(file, "\txor eax, eax\n");
	fprintf(file, "\tcall printf\n");

	fprintf(file, "\n");
	fprintf(file, "\txor eax, eax\n");
	fprintf(file, "\tadd rsp, 8\n");
	fprintf(file, "\tret\n");
}

void code_gen(Vector *ir_code)
{
	file = fopen("output.asm", "w+");

	if (file == NULL)
		error("file 'output.asm' can't be created");

	for (int i = 0; i < ir_code->length; ++i)
	{
		IR *ir = ir_code->data[i];
		if (ir->reg1 > count_R)
			count_R = ir->reg1;
	}

	init_data_section();
	init_text_section();
	start_program();

	for (int i = 0; i < ir_code->length; ++i)
	{
		IR *ir = ir_code->data[i];

		fprintf(file, "\n");

		switch (ir->command)
		{
			case C_LOAD:
				fprintf(file, "\tmov DWORD [R%i], %i\n", ir->reg1, ir->reg2);
				break;
			case C_ADD:
				fprintf(file, "\tmov eax, DWORD [R%i]\n", ir->reg2);
				fprintf(file, "\tadd DWORD [R%i], eax\n", ir->reg1);
				break;
			case C_SUB:
				fprintf(file, "\tmov eax, DWORD [R%i]\n", ir->reg2);
				fprintf(file, "\tsub DWORD [R%i], eax\n", ir->reg1);
				break;
			case C_MUL:
				fprintf(file, "\tmov eax, DWORD [R%i]\n", ir->reg1);
				fprintf(file, "\timul DWORD [R%i]\n", ir->reg2);
				fprintf(file, "\tmov DWORD [R%i], eax\n", ir->reg1);
				break;
			case C_DIV:
				fprintf(file, "\tmov eax, DWORD [R%i]\n", ir->reg1);
				fprintf(file, "\tcdq\n");
				fprintf(file, "\tidiv DWORD [R%i]\n", ir->reg2);
				fprintf(file, "\tmov DWORD [R%i], eax\n", ir->reg1);
				break;
		}
	}

	end_program();

	fclose(file);
}
