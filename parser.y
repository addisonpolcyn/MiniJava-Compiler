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
%token ID INTEGER_LITERAL STRING_LITERAL /* Variables */


%%

Program:
        MainClass ClassDecl
        ;

MainClass:
        CLASS ID OBRACE PUBLIC STATIC VOID MAIN OPARANTHESIS STRING OBRACK EBRACK ID EPARANTHESIS
            OBRACE Statement EBRACE EBRACE
        ;

ClassDecl:
        CLASS ID OBRACE VarDecl MethodDecl EBRACE
        |
        CLASS ID EXTENDS ID OBRACE VarDecl MethodDecl EBRACE
        ;

VarDecl:
        Type ID SEMICOLON
        ;

MethodDecl:
        PUBLIC Type ID OPARANTHESIS FormalList EPARANTHESIS 
            OBRACE VarDecl Statement RETURN Exp SEMICOLON EBRACE
        ;

FormalList:
        Type ID FormalRest
        | /* Empty */
        ;

FormalRest:
        COMMA Type ID
        ;

Type:
        INT
        |
        BOOL
        |
        ID
        |
        Type OBRACK EBRACK
        ;

Statement:
        OBRACE Statement EBRACE
        |
        IF OPARANTHESIS Exp EPARANTHESIS Statement ELSE Statement
        |
        WHILE OPARANTHESIS Exp EPARANTHESIS Statement
        |
        PRINT OPARANTHESIS Exp EPARANTHESIS SEMICOLON
        |
        PRINT OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON
        |
        ID EQUAL Exp SEMICOLON
        |
        ID Index EQUAL Exp SEMICOLON
        ;

Index:
        OBRACK Exp EBRACK
        |
        Index OBRACK Exp EBRACK 
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
        ID Index
        |
        ID DOT LENGTH
        |
        ID Index DOT LENGTH
        |
        INTEGER_LITERAL
        |
        TRUE
        |
        FALSE
        |
        Object
        |
        Object DOT ID OPARANTHESIS ExpList EPARANTHESIS
        ; 

Object:
        ID         
        |
        THIS
        |
        NEW ID OPARANTHESIS EPARANTHESIS
        |
        NEW Type Index
        ;

ExpList:
        ExpRest Exp
        | /* Empty */
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
