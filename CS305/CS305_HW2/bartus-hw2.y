%{
#include <stdio.h>

void yyerror (const char *s) { /* Called by yyparse on error */
    printf ("%s\n", s); }
%}

%token tSTRING
%token tNUM
%token tPRINT
%token tGET
%token tSET
%token tFUNCTION
%token tRETURN
%token tIDENT
%token tIF
%token tEQUALITY
%token tGT
%token tLT
%token tGEQ
%token tLEQ
%token tADD
%token tSUB 
%token tMUL
%token tDIV
%token tINC
%token tDEC

%left '+' '-'
%left '*' '/'
%right '!'
%right UNARY_PLUS UNARY_MINUS

%%
prog :      \[ statement_list \] 
            | \[\]
            ;

statement_list:     statement
                    | statement_list statement
                    ;

statement:      set_statement
                | if_statement
                | print_statement
                | increment_statement
                | decrement_statement
                | return_statement
                | expression_statement
                | get_statement
                | function_statement

set_statement:      \[ tSET [,] tIDENT [,] expression \]
                    ;
if_statement:       \[ tSET [,] condition [,] \[ statement \] \]
                    | \[ tSET [,] condition [,] \[ statement \] [,] \[ statement \] \]

print_statement:        \[ tPRINT [,] expression \]
                        ;
increment_statement:        \[ tINC [,] tIDENT \]
                            ;

decrement_statement:         \[ tDEC [,] tIDENT \]
                             ;
return_statement:           

expression_statement:       \[ expression \]
                            ;

expression:

%%

int main ()
{
   if (yyparse()) {
   // parse error
       printf("ERROR\n");
       return 1;
   }
   else {
   // successful parsing
      printf("OK\n");
      return 0;
   }
}