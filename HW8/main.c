#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define NUM 301
#define SYM 302
#define LPAREN 303
#define RPAREN 304
#define STR 305
int yylex();
extern char attr[256];
void parse_data();
void parse_list();
void parse_list_rest(int first_tok);
void parse_token(int tok);
void parse_data()
{
	int tok = yylex();
	switch (tok)
	{
	case NUM:
		printf("%d", atoi(attr));
		break;
	case SYM:
		printf("%s", attr);
		break;
	case STR:
		printf("%s",attr);
		break;
	case LPAREN:
		parse_list();
		break;
	default:

		exit(1);
	}
}

void parse_list()
{
	int tok;
	printf("(");
	parse_data();

	tok = yylex();
	if (tok == RPAREN)
	{

		printf(" . NIL)");
		return;
	}
	else
	{

		printf(" . ");
		parse_list_rest(tok);
		printf(")");
	}
}

void parse_list_rest(int first_tok)
{

	printf("(");

	parse_token(first_tok);

	int tok = yylex();
	if (tok == RPAREN)
	{
		printf(" . NIL)");
		return;
	}
	else
	{
		printf(" . ");

		parse_list_rest(tok);
		printf(")");
	}
}

void parse_token(int tok)
{
	switch (tok)
	{
	case NUM:
		printf("%d", atoi(attr));
		break;
	case SYM:
		printf("%s", attr);
		break;
	case STR:
		printf("%s",attr);
		break;
	case LPAREN:
		parse_list();
		break;
	default:

		exit(1);
	}
}
int main()
{
	while (true)
	{
		parse_data();
		printf("\n");
	}
	return 0;
}
