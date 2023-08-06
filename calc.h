
#define DEBUG(n) fprintf(stderr, #n" = %f\n", n)

typedef enum {false, true} bool;

/* Order matters! It's the operation Precedence */
enum Operation {
	OP_SUB,
	OP_ADD,
	OP_MUL,
	OP_DIV
};
typedef struct CalcAST {
	enum CalcType {
		CALC_NUM,
		CALC_OP
	} type;
	union {
		struct {
			enum Operation op;
			struct CalcAST *a, *b;
		};
		float num;
	};
} CalcAST;

bool accept_expr(arena *r, char **input, CalcAST *ast);
#define calc_lex accept_expr

bool test();
void calc_print(CalcAST *ast);
bool calc_parse(CalcAST *ast, float *result);
