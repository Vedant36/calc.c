#include <stdio.h>
#include <ctype.h>
#include "calc.h"
#include "arena.h"

/*
  Grammar:
  num ::= 0-9
  op ::= - | + | * | /
  expr ::= num | expr op expr | (expr)
 */

static bool accept_char(char **input, char c)
{
	if ((*input)[0] != c)
		return false;
	(*input)++;
	return true;
}

static bool accept_num(char **input, float *num)
{
	int offset = scanf(" %f ", num);
	if (!offset) return false;
	*input += offset;
	return true;
}

static bool accept_op(char **input, enum Operation *op)
{
	switch ((*input)[0]) {
	case '-': *op = OP_SUB; break;
	case '+': *op = OP_ADD; break;
	case '*': *op = OP_MUL; break;
	case '/': *op = OP_DIV; break;
	default: return false;
	}
	(*input) += 1;
	return true;
}

bool accept_expr(arena *r, char **input, CalcAST *ast)
{
	// Order matters here too! We could accidentally consume a number and
	// leave an incorrect expression: eg. 3 |+ 4 -> '+ 4' is invalid.

	// Case expr op expr
	{
		char **tmp = input;
		ast -> type = CALC_OP;
		if (accept_expr(tmp, ast->a)
			&& accept_op(tmp, &(ast->op))
			&& accept_expr(tmp, ast->b))
			return true;
	}

	// Case (expr)
	{
		char **tmp = input;
		if (accept_char(tmp, '(')
			&& accept_expr(tmp, ast)
			&& accept_char(tmp, ')'))
			return true;
	}

	// Case num
	{
		char **tmp = input;
		ast -> type = CALC_NUM;
		if (accept_num(tmp, &(ast->num)))
			return true;
	}

	return false;
}

