#include "../include/parser.h"

static Token token;

static Node* expr();

static void match_token(int type)
{
	if (token.type != type)
		error("syntax error");
	token = get_next_token();
}

static Node* fact()
{
	Node *n = new_node();

	switch (token.type)
	{
		case NUMBER:
			n->kind  = K_NUM;
			n->value = token.value;
			token    = get_next_token();
			break;

		case LP:
			match_token(LP);
			n = expr();
			match_token(RP);
			break;

		default:
			error("syntax error");
			break;
	}

	return n;
}

static Node* term()
{
	Node *n;
	Node *n1, *n2;
	int saved_char;

	n = fact();

	while (token.type == ASTERISK || token.type == SLASH)
	{
		saved_char = token.type;
		token      = get_next_token();

		n1 = n;
		n2 = fact();

		n      = new_node();
		n->lhs = n1;
		n->rhs = n2;

		switch (saved_char)
		{
			case ASTERISK:     n->kind = K_MULT; break;
			case SLASH: n->kind = K_DIV; break;
		}
	}

	return n;
}

static Node* expr()
{
	Node *n;
	Node *n1, *n2;
	int saved_char;

	n = term();

	while (token.type == PLUS || token.type == MINUS)
	{
		saved_char = token.type;
		token      = get_next_token();

		n1 = n;
		n2 = term();

		n      = new_node();
		n->lhs = n1;
		n->rhs = n2;

		switch (saved_char)
		{
			case PLUS:  n->kind = K_ADD; break;
			case MINUS: n->kind = K_SUB; break;
		}
	}

	return n;
}

Node* parser()
{
	token = get_next_token();

	Node *n = expr();

	if (token.type != EOI)
		error("syntax error");

	return n;
}
