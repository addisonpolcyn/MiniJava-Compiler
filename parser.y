%{
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "node.h"

#define YYDEBUG 1

int yylex();
void yyerror(const char *str);
int yyparse();

extern "C" int yylineno;//, yychar;
extern "C" FILE *yyin;

void yyerror(const char *str)
{
    fprintf(stderr, "Syntax error on line: %d\n", yylineno);
    //fprintf (stderr, "%s\n", str);
}
 
extern "C" int yywrap()
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

%start Program

%union {
    int num;
    char *id;
    Exp *expr;
    Statement *stmt;
    Type *type;
    MethodDecl *method;
    VarDecl *var;
    ClassDecl *classDecl;
    MainClass *main;
    Program *pgm;
}

%define parse.error verbose
%token CLASS PUBLIC STATIC VOID MAIN EXTENDS RETURN /* Declarations */
%token LENGTH PRINTLN PRINT /* Functions */
%token IF ELSE WHILE /* Loops and if-statements */
%token THIS NEW STRING /* Objects */
%token ID INTEGER_LITERAL STRING_LITERAL /* Variables */
%token INT BOOL /* Primitive Types */
%token TRUE FALSE /* booleans */
%token EQUAL NOT DOT /* Operators */
%token AND OR LESS GREATER GREATERTHANEQUAL LESSTHANEQUAL IS ISNOT PLUS MINUS TIMES SLASH /* Binary Operators - op */
%token COMMA SEMICOLON OPARANTHESIS EPARANTHESIS OBRACK EBRACK OBRACE EBRACE QUOTE /* Separators */

%type <num> INTEGER_LITERAL
%type <id> ID
%type <expr> Exp H_Exp I_Exp J_Exp K_Exp L_Exp T_Exp F_Exp G_Exp Root_Exp Object
%type <stmt> Statement
%type <type> Type PrimeType
%type <method> MethodDecl
%type <var> VarDecl
%type <classDecl> ClassDecl
%type <main> MainClass
%type <pgm> Program

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
        |
        ID EQUAL Exp SEMICOLON
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

PrimeType:
        INT
        |
        BOOL
        |
        ID
        ;

Type:
        PrimeType
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
        PRINTLN OPARANTHESIS Exp EPARANTHESIS SEMICOLON
        |
        PRINTLN OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON
        |
        PRINT OPARANTHESIS Exp EPARANTHESIS SEMICOLON
        |
        PRINT OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON
        |
        ID EQUAL Exp SEMICOLON
        |
        ID Index EQUAL Exp SEMICOLON
        |
        RETURN Exp SEMICOLON
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
        Exp OR T_Exp
        |
        T_Exp
        ;

T_Exp:
        T_Exp AND F_Exp { $$ = new And($1, $3); std::cout << "fired And #############\n"; }
        |
        F_Exp
        ;

F_Exp:
        F_Exp IS G_Exp
        |
        F_Exp ISNOT G_Exp
        |
        G_Exp
        ;

G_Exp:
        G_Exp LESS H_Exp { $$ = new LessThan($1, $3); std::cout << "fired Less #############\n"; }
        |
        G_Exp LESSTHANEQUAL H_Exp
        |
        G_Exp GREATER H_Exp
        |
        G_Exp GREATERTHANEQUAL H_Exp
        |
        H_Exp
        ;

H_Exp:
        H_Exp PLUS I_Exp { $$ = new Plus($1, $3); std::cout << "fired Plus #############\n"; }
        |
        H_Exp MINUS I_Exp { $$ = new Minus($1, $3); std::cout << "fired Minus #############\n"; }
        |
        I_Exp
        ;

I_Exp:
        I_Exp TIMES J_Exp { $$ = new Times($1, $3); std::cout << "fired Times #############\n"; }
        |
        I_Exp SLASH J_Exp
        |
        J_Exp
        ;

J_Exp:
        PLUS K_Exp
        |
        MINUS K_Exp 
        |
        NOT K_Exp { $$ = new Not($2); std::cout << "fired Not #############\n"; }
        |
        K_Exp
        ;

K_Exp:
        K_Exp DOT LENGTH
        |
        K_Exp DOT ID OPARANTHESIS ExpList EPARANTHESIS
        |
        L_Exp
        ;

L_Exp:
        ID Root_Exp DOT LENGTH
        |
        Root_Exp
        ;
        
Root_Exp:  
        OPARANTHESIS Exp EPARANTHESIS { $$ = $2; std::cout << "fired (exp)"; }
        |
        ID Index
        |
        INTEGER_LITERAL
        |
        TRUE { $$ = new True(); std::cout << "fired True #############\n"; }
        |
        FALSE { $$ = new False(); std::cout << "fired False #############\n"; }
        |
        Object
        ;  

Object:
        ID { $$ = new IdentifierExp($1); std::cout << "fired IdentExp #############\n"; }
        |
        THIS { $$ = new This(); std::cout << "fired This #############\n"; }
        |
        NEW ID OPARANTHESIS EPARANTHESIS
        |
        NEW PrimeType Index
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

%%
