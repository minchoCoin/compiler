all: main

main: lex.yy.c main.c
	gcc lex.yy.c main.c -o main

lex.yy.c: data.lex
	flex data.lex

clean:
	rm main lex.yy.c

test:
	./main < main.c

zip: Makefile data.lex main.c
	zip main.zip Makefile data.lex main.c

