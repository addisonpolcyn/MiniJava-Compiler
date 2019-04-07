%{
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>
#include "node.h"

#define YYDEBUG 1
#define PRINTDEBUG(x) std::cout << x; // comment out print statement to remove the printing

//root of AST
Program *root;

int yylex();
void yyerror(const char *str);
int yyparse();

extern "C" int yylineno;
extern "C" FILE *yyin;

void yyerror(const char *str)
{
    fprintf(stderr, "Syntax error on line: %d\n", yylineno);
}
 
extern "C" int yywrap()
{
    return 1;
} 
  
int main(int argc, char **argv) {
    /* Process file as command line args */
    yyin = fopen(argv[1], "r");
    
    /* Parse file and build AST */
    yyparse();
    fclose(yyin);

    /* Traverse AST */
    root->evaluate();

    /* Finish */
    return 0;
}

%}

%start Program

%union {
    /* Terminals */
    int num;
    char *id;
    char *str;

    /* Non-Terminals */
    Exp *expr;
    Statement *stmt;
    Type *type;
    Formal *formal;
    MethodDecl *method;
    VarDecl *var;
    ClassDecl *classDecl;
    MainClass *main;
    Program *pgm;

    /* Lists */
    std::list<ClassDecl *> *classDeclList;
    std::list<Exp *> *expList;
    std::list<Formal *> *formalList;
    std::list<MethodDecl *> *methodDeclList;
    std::list<Statement *> *stmtList;
    std::list<VarDecl *> *varDeclList;
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

/* Terminals */
%type <num> INTEGER_LITERAL
%type <str> STRING_LITERAL
%type <id> ID

/* Non-Terminals */
%type <expr> Exp H_Exp I_Exp J_Exp K_Exp L_Exp T_Exp F_Exp G_Exp Root_Exp Object
%type <stmt> Statement 
%type <type> Type PrimeType 
%type <formal> FormalRest
%type <method> MethodDecl
%type <var> VarDecl
%type <classDecl> ClassDecl
%type <main> MainClass
%type <pgm> Program

/* Lists */
%type <classDeclList> ClassDeclList
%type <expList> ExpList
%type <formalList> FormalList FormalRestList
%type <methodDeclList> MethodDeclList
%type <stmtList> StatementList
%type <varDeclList> VarDeclList

%%

Program:
        MainClass ClassDeclList
        { $$ = new Program($1, $2); root = $$; PRINTDEBUG("fired Program $$$$$$$$$$$$$$$\n") }
        ;

MainClass:
        CLASS ID OBRACE PUBLIC STATIC VOID MAIN OPARANTHESIS STRING OBRACK EBRACK ID EPARANTHESIS
            OBRACE Statement EBRACE EBRACE
        { $$ = new MainClass(new Identifier($2), new Identifier($12), $15); PRINTDEBUG("fired Main #############\n") }
        ;

ClassDecl:
        CLASS ID OBRACE VarDeclList MethodDeclList EBRACE 
        { $$ = new ClassDeclSimple(new Identifier($2), $4, $5); PRINTDEBUG("fired Class Decl Simple ############\n") }
        |
        CLASS ID EXTENDS ID OBRACE VarDeclList MethodDeclList EBRACE
        { $$ = new ClassDeclExtends(new Identifier($2), new Identifier($4), $6, $7); PRINTDEBUG("fired Class Decl Extends ###########\n") }
        ;

ClassDeclList:
        ClassDeclList ClassDecl { PRINTDEBUG("class list wanted upstream ^^^^^^^^^^^^^^^^^^^^^\n"); $$ = $1; $1->push_back($2); PRINTDEBUG("loaded up classdecl list push\n") }
        | /* Empty */  { PRINTDEBUG("class list wanted DOWNSTREAM EMPTY\n"); $$ = new std::list<ClassDecl *>(); PRINTDEBUG("alocated new list\n") }
        ;

VarDecl:
        PrimeType ID SEMICOLON { $$ = new VarDecl($1, new Identifier($2)); PRINTDEBUG("fired Var Decl ###############\n") }
        ;

VarDeclList:
        VarDeclList VarDecl { $$ = $1; $1->push_back($2); PRINTDEBUG("loaded up vardecl list push\n") }
        | /* Empty */  { PRINTDEBUG("var list EMPTY\n") $$ = new std::list<VarDecl *>(); PRINTDEBUG("alocated new list\n") }
        ;

MethodDecl:
        PUBLIC Type ID OPARANTHESIS FormalList EPARANTHESIS 
            OBRACE VarDeclList StatementList RETURN Exp SEMICOLON EBRACE
        { $$ = new MethodDecl($2, new Identifier($3), $5, $8, $9, $11); PRINTDEBUG("fired method decl ######################\n") }
        ;

MethodDeclList:
        MethodDeclList MethodDecl { PRINTDEBUG("method list wanted upstream ^^^^^^^^^^^^^^^^^^^^^\n");
        $$ = $1; $1->push_back($2); PRINTDEBUG("loaded up methoddecl list push\n") }
        | /* Empty */  {  PRINTDEBUG("method list wanted DOWNSTREAM EMPTY\n"); $$ = new std::list<MethodDecl *>(); PRINTDEBUG("alocated new list\n") }
        ;

FormalList:
        Type ID FormalRestList { $$ = new std::list<Formal *>(); $$->push_back(new Formal($1, new Identifier($2)));
        PRINTDEBUG("formal list wanted upstream&&&&&&&&&&&&&&&&& ^^^^^^^^^^^^^^^^^^^^^\n") }
        | /* Empty */ { $$ = new std::list<Formal *>(); PRINTDEBUG("formlist empty, creating new list") }
        ;

FormalRest:
        COMMA Type ID { }
        ;

FormalRestList:
        FormalRestList FormalRest { $$=$1; $1->push_back($2); PRINTDEBUG("fired formal @@@@@@@@@@@@@@@2\n"); 
        PRINTDEBUG("formal rest list list wanted upstream ??????????????????????????\n") }
        | /* Empty */
        ;

PrimeType:
        INT { $$ = new IntegerType(); PRINTDEBUG("fired int type #############\n") }
        |
        BOOL { $$ = new BooleanType(); PRINTDEBUG("fired bool type #############\n") } 
        ;

Type:
        ID { $$ = new IdentifierType($1); PRINTDEBUG("fired id type #############\n") }
        |
        Type OBRACK EBRACK { $$ = new IntArrayType(); PRINTDEBUG("fired int array type #############\n") }
        |
        PrimeType 
        ;

Statement:
        OBRACE StatementList EBRACE { PRINTDEBUG("fired statementList ################") $$ = new Block($2); }
        |
        IF OPARANTHESIS Exp EPARANTHESIS Statement ELSE Statement { $$ = new If($3, $5, $7); PRINTDEBUG("fired If #############\n") }
        |
        WHILE OPARANTHESIS Exp EPARANTHESIS Statement { $$ = new While($3, $5); PRINTDEBUG("fired While #############\n") }
        |
        PRINTLN OPARANTHESIS Exp EPARANTHESIS SEMICOLON { $$ = new Println($3); PRINTDEBUG("fired Println #############\n") }
        |
        PRINTLN OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON { $$ = new PrintStringln($3); PRINTDEBUG("fired println Stringlit ############") }
        |
        PRINT OPARANTHESIS Exp EPARANTHESIS SEMICOLON { $$ = new Print($3); PRINTDEBUG("fired Print #############\n") }
        |
        PRINT OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON { $$ = new PrintString($3); PRINTDEBUG("fired print string lit ################") }
        |
        ID EQUAL Exp SEMICOLON { $$ = new Assign(new Identifier($1), $3); PRINTDEBUG("fired Assign #############\n") }
        |
        ID Index EQUAL Exp SEMICOLON { PRINTDEBUG("fired ArrayAssign @@@@@@@@@@@\n") }
        |
        RETURN Exp SEMICOLON { PRINTDEBUG("fired return @@@@@@@@@@@@@@@@@@@") }
        ;

StatementList:
        StatementList Statement { PRINTDEBUG("statment list wanted upstream ^^^^^^^^^^^^^^^^^^^^^\n")
        $$ = $1, $1->push_back($2); 
        PRINTDEBUG("loaded stmt list\n") }
        | /* Empty */ { PRINTDEBUG("empty stmt list\n") 
        $$ = new std::list<Statement *>(); PRINTDEBUG("built stmt list\n") }
        ;

Index:
        OBRACK Exp EBRACK { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> index (exp)\n") }
        |
        Index OBRACK Exp EBRACK { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> index [exp]\n") }
       ;

Exp: 
        Exp OR T_Exp { $$ = new Or($1, $3); PRINTDEBUG("fired exp OR #################\n") }
        |
        T_Exp
        ;

T_Exp:
        T_Exp AND F_Exp { $$ = new And($1, $3); PRINTDEBUG("fired And #############\n") }
        |
        F_Exp
        ;

F_Exp:
        F_Exp IS G_Exp { $$ = new Is($1, $3); PRINTDEBUG("fired exp == #################\n") }
        |
        F_Exp ISNOT G_Exp { $$ = new IsNot($1, $3); PRINTDEBUG("fired exp != #################\n") }
        |
        G_Exp
        ;

G_Exp:
        G_Exp LESS H_Exp { $$ = new LessThan($1, $3); PRINTDEBUG("fired Less #############\n") }
        |
        G_Exp LESSTHANEQUAL H_Exp { $$ = new LessThanEqual($1, $3); PRINTDEBUG("fired lessthanequl #############\n") }
        |
        G_Exp GREATER H_Exp { $$ = new GreaterThan($1, $3); PRINTDEBUG("fired greater ###############\n") }
        |
        G_Exp GREATERTHANEQUAL H_Exp { $$ = new GreaterThanEqual($1, $3); PRINTDEBUG("fired greaterthanequal ###############\n") }
        |
        H_Exp
        ;

H_Exp:
        H_Exp PLUS I_Exp { $$ = new Plus($1, $3); PRINTDEBUG("fired Plus #############\n") }
        |
        H_Exp MINUS I_Exp { $$ = new Minus($1, $3); PRINTDEBUG("fired Minus #############\n") }
        |
        I_Exp
        ;

I_Exp:
        I_Exp TIMES J_Exp { $$ = new Times($1, $3); PRINTDEBUG("fired Times #############\n") }
        |
        I_Exp SLASH J_Exp { $$ = new Div($1, $3); PRINTDEBUG("fired exp division ##############\n") }
        |
        J_Exp
        ;

J_Exp:
        PLUS K_Exp { $$ = new PositiveExp($2); PRINTDEBUG("fired exp (+) #############\n") }
        |
        MINUS K_Exp  { $$ = new NegativeExp($2); PRINTDEBUG("fired exp (-) ##############\n") }
        |
        NOT K_Exp { $$ = new Not($2); PRINTDEBUG("fired Not #############\n") }
        |
        K_Exp
        ;

K_Exp:
        K_Exp DOT LENGTH { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exp dot length\n") }
        |
        K_Exp DOT ID OPARANTHESIS ExpList EPARANTHESIS { $$ = new Call($1, new Identifier($3), $5); 
        PRINTDEBUG("call exp #########################3\n") }
        |
        L_Exp
        ;

L_Exp:
        ID Root_Exp DOT LENGTH { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exp length\n") }
        |
        Root_Exp
        ;
        
Root_Exp:  
        OPARANTHESIS Exp EPARANTHESIS { $$ = $2; PRINTDEBUG("fired (exp) ###########") }
        |
        ID Index { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exp id index\n") }
        |
        INTEGER_LITERAL { $$ = new IntegerLiteral($1); PRINTDEBUG("fired integer literal ###########\n") }
        |
        TRUE { $$ = new True(); PRINTDEBUG("fired True #############\n") }
        |
        FALSE { $$ = new False(); PRINTDEBUG("fired False #############\n") }
        |
        Object
        ;  

Object:
        ID { $$ = new IdentifierExp($1); PRINTDEBUG("fired IdentExp #############\n") }
        |
        THIS { $$ = new This(); PRINTDEBUG("fired This #############\n") }
        |
        NEW ID OPARANTHESIS EPARANTHESIS { $$ = new NewObject(new Identifier($2)); PRINTDEBUG("fired exp new id() ###############\n") }
        |
        NEW PrimeType Index { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX exp new object prime\n") }
        ;

ExpList:
        Exp ExpRestList { PRINTDEBUG("@@@@@@@@@@gubub&*^%#TESTTESTTESTTESTTEST> exp exprest list\n") } 
        | /* Empty */ { $$ = new std::list<Exp *>(); PRINTDEBUG("explist empty, creating new list") }
        ;

ExpRest:
        COMMA Exp { PRINTDEBUG("@@@@@@@@@@@@@@@@TESTTESTESTESTESTES> exprest comma\n")
        /*$$->push_back($2); std::cout << "loaded up classdecl list push\n";*/ }
        ;

ExpRestList:
        ExpRestList ExpRest { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exprestlist") } 
        | /* Empty */
        ;

%%
