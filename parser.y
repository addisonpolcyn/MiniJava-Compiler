%{
#include <stdio.h>
#include <string.h>

int yylex();
void yyerror(char *str);
int yyparse();

extern int yylineno, yychar;
FILE *yyin;

void yyerror(s)
char *s;
{
    fprintf(stderr, "Syntax error on line: %d\n", yylineno);
}
 
int yywrap()
{
        return 1;
} 
  
int main(int argc, char **argv) {
    /* Process file as command line args */
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    return 0;
}

%}

%token NUMBER TOKHEAT STATE TOKTARGET TOKTEMPERATURE

%token CLASS PUBLIC STATIC VOID MAIN EXTENDS RETURN /* Declarations */
%token LENGTH PRINT /* Functions */
%token THIS NEW STRING /* Objects */
%token INT BOOL /* Primitive Types */
%token IF ELSE WHILE /* Loops and if-statements */
%token TRUE FALSE /* booleans */
%token COMMA SEMICOLON OPARANTHESIS EPARANTHESIS OBRACK EBRACK OBRACE EBRACE QUOTE /* Separators */
%token EQUAL PLUSPLUS NOT DOT /* Operators */
%token AND OR LESS GREATER GREATERTHANEQUAL LESSTHANEQUAL IS ISNOT PLUS MINUS TIMES SLASH /* Binary Operators - op */

%%

commands: /* empty */
        | commands command
        ;

command:
        heat_switch
        |
        target_set
        |
        ping
        ;

heat_switch:
        TOKHEAT STATE
        {
            if($2) {
                printf("\tHeat turned on\n");
            } else {
                printf("\tHeat turned off\n");
            }
        }
        ;

target_set:
        TOKTARGET TOKTEMPERATURE NUMBER
        {
                printf("\tTemperature set to %d\n",$3);
        }
        ;

ping:
        NUMBER
        {
                printf("\tnumber\n");
        }
	|
	STATE
        {
                printf("\tstate\n");
        }
        ;

Exp:
        Exp op Exp
        |
        NOT Exp
        |
        PLUS Exp
        |
        MINUS Exp
        |
        OPARANTHESIS Exp EPARANTHESIS
        |
        /* TBD */
        ; 

Object:
        |

ExpList:
        | ExpRest Exp
        ;

ExpRest:
        COMMA Exp
        ;

op:     /* Binary Operators */
        AND
        |
        OR
        |
        LESS
        |
        GREATER
        |
        GREATERTHANEQUAL
        |
        LESSTHANEQUAL
        |
        IS
        |
        ISNOT
        |
        PLUS
        |
        MINUS
        |
        TIMES
        |
        SLASH
        ;

%%
