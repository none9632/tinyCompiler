#include "../include/lexer.h"

static char *input_str;

static Token get_num_token()
{
	Token token;

	token.type  = NUMBER;
	token.value = 0;
	input_str--;

	while (isdigit(*input_str))
	{
		token.value = token.value * 10 + *input_str - '0';
		input_str++;
	}

	return token;
}

Token get_next_token()
{
	Token token;
	char symbol = *input_str++;

	while (isspace(symbol))
		symbol = *input_str++;

	switch (symbol)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			token = get_num_token();
			break;
		case '(':
			token.type = LP;
			break;
		case ')':
			token.type = RP;
			break;
		case '+':
			token.type = PLUS;
			break;
		case '-':
			token.type = MINUS;
			break;
		case '*':
			token.type = ASTERISK;
			break;
		case '/':
			token.type = SLASH;
			break;
		case '\0':
			token.type = EOI;
			break;
		default:
			error("unknown character");
			break;
	}

	return token;
}

void init_lexer(char *_input_str)
{
	input_str = _input_str;
}