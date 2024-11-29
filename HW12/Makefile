all:main

main: lex.yy.c y.tab.c y.tab.h ast.h
		gcc lex.yy.c y.tab.c ast.c -o main

lex.yy.c: token.l y.tab.h ast.h
		flex token.l

y.tab.c: ast.y ast.h
		bison -dy ast.y

y.tab.h: ast.y ast.h
		bison -dy ast.y

clean: main lex.yy.c y.tab.c y.tab.h
		rm main lex.yy.c y.tab.c y.tab.h
zip: Makefile token.l ast.y ast.c ast.h
	zip main.zip Makefile token.l ast.y ast.c ast.h