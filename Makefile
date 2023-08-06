

run: calc
	./calc

calc: calc.c lexer.c
	gcc -Werror -Wall -Wextra -Wno-unused -Wno-infinite-recursion -ggdb lexer.c calc.c -o calc
