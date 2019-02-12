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

%token CLASS PUBLIC STATIC VOID MAIN EXTENDS RETURN /* Declarations */
%token LENGTH PRINT /* Functions */
%token IF ELSE WHILE /* Loops and if-statements */

%token THIS NEW STRING /* Objects */
%token ID INTEGER_LITERAL STRING_LITERAL /* Variables */
%token INT BOOL /* Primitive Types */
%token TRUE FALSE /* booleans */

%token EQUAL PLUSPLUS NOT DOT /* Operators */
%token AND OR LESS GREATER GREATERTHANEQUAL LESSTHANEQUAL IS ISNOT PLUS MINUS TIMES SLASH /* Binary Operators - op */

%token COMMA SEMICOLON OPARANTHESIS EPARANTHESIS OBRACK EBRACK OBRACE EBRACE QUOTE /* Separators */

%%

Program:
        MainClass ClassDeclList
        ;

MainClass:
        CLASS ID OBRACE PUBLIC STATIC VOID MAIN OPARANTHESIS STRING OBRACK EBRACK ID EPARANTHESIS
            OBRACE Statement EBRACE EBRACE
        ;

ClassDecl:
        CLASS ID OBRACE VarDeclList MethodDeclList EBRACE
        |
        CLASS ID EXTENDS ID OBRACE VarDeclList MethodDeclList EBRACE
        ;

ClassDeclList:
        ClassDeclList ClassDecl
        | /* Empty */
        ;

VarDecl:
        Type ID SEMICOLON
        ;

VarDeclList:
        VarDeclList VarDecl
        | /* Empty */
        ;

MethodDecl:
        PUBLIC Type ID OPARANTHESIS FormalList EPARANTHESIS 
            OBRACE VarDeclList StatementList RETURN Exp SEMICOLON EBRACE
        ;

MethodDeclList:
        MethodDeclList MethodDecl
        | /* Empty */
        ;

FormalList:
        Type ID FormalRestList
        | /* Empty */
        ;

FormalRest:
        COMMA Type ID
        ;

FormalRestList:
        FormalRestList FormalRest
        | /* Empty */
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
        OBRACE StatementList EBRACE
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

StatementList:
        StatementList Statement
        | /* Empty */
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
        Exp ExpRestList
        | /* Empty */
        ;

ExpRest:
        COMMA Exp
        ;

ExpRestList:
        ExpRestList ExpRest
        | /* Empty */
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
