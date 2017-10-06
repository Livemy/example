%{
#define YYSTYPE double
#include <stdio.h>
#include <math.h>
#include <ctype.h>
%}

/* ���岿�� */
%token NUM
%left '-' '+'
%left '*' '/'
%right '^'       /* ָ������   */

/* ���򲿷� */

%%
input:		  /* �մ� */
       		| input line
     		;
     
line:		  '\n'
			| exp '\n'  { printf ("\t%.10g\n", $1); }
			;
     
exp:		  NUM                { $$ = $1;         }
			| exp '+' exp        { $$ = $1 + $3;    }
     		| exp '-' exp        { $$ = $1 - $3;    }
       		| exp '*' exp        { $$ = $1 * $3;    }
 			| exp '/' exp        { $$ = $1 / $3;    }
			| exp '^' exp        { $$ = pow ($1, $3); }
			| '(' exp ')'        { $$ = $2;         }
     		;
%% 
/* �û����벿��ͬ������2.1һ�����ڴ�ʡ��*/

main ()	/* ������ */
	{
     yyparse ();
	}

yyerror (s)  /* �﷨��������yyparse()����ʱ���øú��� */
 	char *s;
	{
   	printf ("%s\n", s);
	}
/* yyparse()�ڶ������ļ����дʷ�����ʱ��ͨ�����ôʷ���������yylex()��
   �õ�ǰ�ʻ�ı��룬�ڴ������ṩһ���ֹ���д�Ĵʷ������������ú����ڷ���
   �ʻ�ı����ͬʱ��������ʻ������ֵyylval��������ֵ���ʹʻ���һ��
   �ƽ�����ջ */
 
int yylex ()
	{
	int c;
 
	/* �������ַ� */
	while ((c = getchar ()) == ' ' || c == '\t')
	;
	/* ��������   */
	if (c == '.' || isdigit (c))
		{
		ungetc (c, stdin);
		scanf ("%lf", &yylval); /* ȫ�ֱ���yylval��¼��ǰ���ε�
					����ֵ������y.tab.c�ж��壬�����������ɶ��岿��
					������ĺ�YYSTYPE��������˫������double */
		return NUM; /* �������ֶ�Ӧ�Ĵʻ����NUM��YACC�����岿�ֵ�
				"%token NUM"����ΪC�ĺ궨��"#define NUM XXX"
				�����y.tab.c�У���ˣ��ڴ˿�ֱ��ʹ�ú���NUM */
		}
       /* �ļ�����ʱ������0 */
	if (c == EOF)
         return 0;
       /* �����ַ���ASCII�룬���﷨�����Ե����ַ���ʽ���ֵ��ս������' ' ��
  		 �ڶ��岿�ֲ���Ҫ��%token������������Ĵʻ��������ASCII�� */
	return c;
	}
