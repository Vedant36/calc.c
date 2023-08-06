
/*
 * Calculator Program
 */
#include <assert.h>
#include <stdio.h>
#include "calc.h"
#define ARENA_IMPLEMENTATION
#include "arena.h"

void calc_test_lexing(char *test_string);

int main()
{
	bool success = test();
	if(success)
		printf("Tests successful!\n");
	return !success;
}

bool test()
{
	/* bool success = true; */
	/* float result; */
	/* CalcAST calc1 = {.type = CALC_NUM, .num = 3}; */
 	/* CalcAST calc2 = {.type = CALC_NUM, .num = 5}; */
	/* CalcAST calc3 = { */
	/* 	.type = CALC_OP, */
	/* 	.op = OP_ADD, */
	/* 	.a = &calc1, */
	/* 	.b = &calc2 */
	/* }; */
	/* CalcAST calc4 = { */
	/* 	.type = CALC_OP, */
	/* 	.op = OP_ADD, */
	/* 	.a = &calc3, */
	/* 	.b = &calc2 */
	/* }; */
	/* success &= calc_parse(&calc1, &result); */
	/* printf("Result 1: %f\n", result); */
	/* success &= calc_parse(&calc2, &result); */
	/* printf("Result 2: %f\n", result); */
	/* success &= calc_parse(&calc3, &result); */
	/* printf("Result 3: %f\n", result); */

	/* printf("Repr calc3: "); */
	/* calc_print(&calc4); */
	/* printf("\n"); */

	arena main = arena_create(1 * 1024 * 1024); /* 1mb */
	calc_test_lexing(&main, "ABCD");
	calc_test_lexing(&main, "");
	calc_test_lexing(&main, "3");
	calc_test_lexing(&main, "3 + 4");
	calc_test_lexing(&main, "()");
	calc_test_lexing(&main, "(2 +5)");
	calc_test_lexing(&main, "4 + (1 + 9)");

	return true;
}

void calc_test_lexing(char *test_string)
{
	CalcAST ast = {0};
	bool success = calc_lex(&test_string, &ast);
	printf("%s: %s -> ", success ? "Successful" : "    Failed"
		, test_string);
	calc_print(&ast);
	printf("\n");
}

void calc_print(CalcAST *ast)
{
	switch (ast->type) {
	case CALC_NUM:
		printf("%.0f", ast->num);
		break;
	case CALC_OP:
		printf("(");
		calc_print(ast->a);
		switch (ast->op) {
		case OP_ADD:
			printf(" + ");
			break;
		case OP_SUB:
			printf(" - ");
			break;
		case OP_MUL:
			printf(" * ");
			break;
		case OP_DIV:
			printf(" / ");
			break;
		}
		calc_print(ast->b);
		printf(")");
		break;
	}
}

/* (1 + 3)
 * ((*)) -> (*)
 * n
 * input needs to be null terminated
 */
/* In this case the lexer always provides a correct AST */
bool calc_parse(CalcAST *ast, float *result)
{
	switch (ast->type) {
	case CALC_NUM:
		*result = ast->num;
		break;
	case CALC_OP:
		float a, b;
		calc_parse(ast->a, &a);
		calc_parse(ast->b, &b);
		switch (ast->op) {
		case OP_ADD:
			*result = a + b;
			break;
		case OP_SUB:
			*result = a - b;
			break;
		case OP_MUL:
			*result = a * b;
			break;
		case OP_DIV:
			*result = a / b;
			break;
		}
		break;
	}
	return true;
}
