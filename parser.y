%{
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>
#include "node.h"

#define YYDEBUG 1
#define PRINTDEBUG(x)  std::cout << x << std::endl;// comment out print statement to remove the printing

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
    exit(1);
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
    root->traverse();
    
    /* Convert AST To ARM */
    root->compile();

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
%type <expr> Exp H_Exp I_Exp J_Exp K_Exp L_Exp T_Exp F_Exp G_Exp Root_Exp Object ExpRest Index
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
%type <expList> ExpList ExpRestList
%type <formalList> FormalList FormalRestList
%type <methodDeclList> MethodDeclList
%type <stmtList> StatementList
%type <varDeclList> VarDeclList


%%

Program:
        MainClass ClassDeclList
        { $$ = new Program($1, $2, yylineno); root = $$; PRINTDEBUG("fired Program $$$$$$$$$$$$$$$\n") }
        ;

MainClass:
        CLASS ID OBRACE PUBLIC STATIC VOID MAIN OPARANTHESIS STRING OBRACK EBRACK ID EPARANTHESIS
            OBRACE Statement EBRACE EBRACE
        { $$ = new MainClass(new Identifier($2), new Identifier($12), $15); PRINTDEBUG("fired Main #############\n") }
        ;

ClassDecl:
        CLASS ID OBRACE VarDeclList MethodDeclList EBRACE 
        { $$ = new ClassDeclSimple(new Identifier($2), $4, $5, yylineno); PRINTDEBUG("fired Class Decl Simple ############\n") }
        |
        CLASS ID EXTENDS ID OBRACE VarDeclList MethodDeclList EBRACE
        { $$ = new ClassDeclExtends(new Identifier($2), new Identifier($4), $6, $7, yylineno); PRINTDEBUG("fired Class Decl Extends ###########\n") }
        ;

ClassDeclList:
        ClassDeclList ClassDecl { PRINTDEBUG("class list wanted upstream"); $$ = $1; $1->push_back($2); PRINTDEBUG("loaded up classdecl list push\n") }
        | /* Empty */  { PRINTDEBUG("class list wanted DOWNSTREAM EMPTY"); $$ = new std::list<ClassDecl *>(); PRINTDEBUG("alocated new list") }
        ;

VarDecl:
        Type ID SEMICOLON { $$ = new VarDecl($1, new Identifier($2)); PRINTDEBUG("fired Var Decl ###############\n") }
        ;

VarDeclList:
        VarDeclList VarDecl { $$ = $1; $1->push_back($2); PRINTDEBUG("loaded up vardecl list push\n") }
        | /* Empty */  { PRINTDEBUG("var list EMPTY\n") $$ = new std::list<VarDecl *>(); PRINTDEBUG("alocated new list\n") }
        ;

MethodDecl:
        PUBLIC Type ID OPARANTHESIS FormalList EPARANTHESIS 
            OBRACE VarDeclList StatementList RETURN Exp SEMICOLON EBRACE
        { $$ = new MethodDecl($2, new Identifier($3), $5, $8, $9, $11, yylineno); PRINTDEBUG("fired method decl ######################\n") }
        ;

MethodDeclList:
        MethodDeclList MethodDecl { PRINTDEBUG("(method list wanted upstream)");
        $$ = $1; $1->push_back($2); PRINTDEBUG("(loaded up methoddecl list push)") }
        | /* Empty */  {  PRINTDEBUG("(method list wanted DOWNSTREAM EMPTY)"); $$ = new std::list<MethodDecl *>(); PRINTDEBUG("(alocated new list)") }
        ;

FormalList:
        Type ID FormalRestList { $$ = $3; $$->push_back(new Formal($1, new Identifier($2))); PRINTDEBUG("Wrapping up formal list\n") }
        | { $$ = new std::list<Formal *>(); PRINTDEBUG("formlist empty creating dummy list ##############") }
        ;

FormalRest:
        COMMA Type ID { $$ = new Formal($2, new Identifier($3)); PRINTDEBUG("loaded FormalRest>>>>>>>>>>>>>>>>>>") }
        ;

FormalRestList:
        FormalRestList FormalRest { $$ = $1; $$->push_back($2); PRINTDEBUG("fired formal") }
        | { $$ = new std::list<Formal *>(); PRINTDEBUG("formal list finished") }
        ;

PrimeType:
        /*ID { $$ = new IdentifierType($1); PRINTDEBUG("fired id type #############\n") }
        |*/
        INT { $$ = new IntegerType(); PRINTDEBUG("fired int type #############\n") }
        |
        BOOL { $$ = new BooleanType(); PRINTDEBUG("fired bool type #############\n") } 
        ;

Type:
        PrimeType 
        |
        Type OBRACK EBRACK { $$ = new IntArrayType(); PRINTDEBUG("fired int array type #############\n") }
        ;

Statement:
        OBRACE StatementList EBRACE { PRINTDEBUG("fired statementList ################") $$ = new Block($2); }
        |
        IF OPARANTHESIS Exp EPARANTHESIS Statement ELSE Statement { $$ = new If($3, $5, $7, yylineno); PRINTDEBUG("fired If #############\n") }
        |
        WHILE OPARANTHESIS Exp EPARANTHESIS Statement { $$ = new While($3, $5, yylineno); PRINTDEBUG("fired While #############\n") }
        |
        PRINTLN OPARANTHESIS Exp EPARANTHESIS SEMICOLON { $$ = new Println($3, yylineno); PRINTDEBUG("fired Println #############\n") }
        |
        PRINTLN OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON { $$ = new PrintStringln($3); PRINTDEBUG("fired println Stringlit ############") }
        |
        PRINT OPARANTHESIS Exp EPARANTHESIS SEMICOLON { $$ = new Print($3, yylineno); PRINTDEBUG("fired Print #############\n") }
        |
        PRINT OPARANTHESIS STRING_LITERAL EPARANTHESIS SEMICOLON { $$ = new PrintString($3); PRINTDEBUG("fired print string lit ################") }
        |
        ID EQUAL Exp SEMICOLON { $$ = new Assign(new Identifier($1), $3, yylineno); PRINTDEBUG("fired Assign #############\n") }
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
        OBRACK Exp EBRACK { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> index (exp)\n")
        $$ = new Index($2); }
        |
        Index OBRACK Exp EBRACK { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> index  empty [exp]\n") 
        $$ = new Index($3); PRINTDEBUG("exp list expr") }
        ;
 
Exp: 
        Exp OR T_Exp { $$ = new Or($1, $3, yylineno); PRINTDEBUG("fired exp OR #################\n") }
        |
        T_Exp
        ;

T_Exp:
        T_Exp AND F_Exp { $$ = new And($1, $3, yylineno); PRINTDEBUG("fired And #############\n") }
        |
        F_Exp
        ;

F_Exp:
        F_Exp IS G_Exp { $$ = new Is($1, $3, yylineno); PRINTDEBUG("fired exp == #################\n") }
        |
        F_Exp ISNOT G_Exp { $$ = new IsNot($1, $3, yylineno); PRINTDEBUG("fired exp != #################\n") }
        |
        G_Exp
        ;

G_Exp:
        G_Exp LESS H_Exp { $$ = new LessThan($1, $3, yylineno); PRINTDEBUG("fired Less #############\n") }
        |
        G_Exp LESSTHANEQUAL H_Exp { $$ = new LessThanEqual($1, $3, yylineno); PRINTDEBUG("fired lessthanequl #############\n") }
        |
        G_Exp GREATER H_Exp { $$ = new GreaterThan($1, $3, yylineno); PRINTDEBUG("fired greater ###############\n") }
        |
        G_Exp GREATERTHANEQUAL H_Exp { $$ = new GreaterThanEqual($1, $3, yylineno); PRINTDEBUG("fired greaterthanequal ###############\n") }
        |
        H_Exp
        ;

H_Exp:
        H_Exp PLUS I_Exp { $$ = new Plus($1, $3, yylineno); PRINTDEBUG("fired Plus #############\n") }
        |
        H_Exp MINUS I_Exp { $$ = new Minus($1, $3, yylineno); PRINTDEBUG("fired Minus #############\n") }
        |
        I_Exp
        ;

I_Exp:
        I_Exp TIMES J_Exp { $$ = new Times($1, $3, yylineno); PRINTDEBUG("fired Times #############\n") }
        |
        I_Exp SLASH J_Exp { $$ = new Div($1, $3, yylineno); PRINTDEBUG("fired exp division ##############\n") }
        |
        J_Exp
        ;

J_Exp:
        PLUS K_Exp { $$ = new PositiveExp($2, yylineno); PRINTDEBUG("fired exp (+)") }
        |
        MINUS K_Exp  { $$ = new NegativeExp($2, yylineno); PRINTDEBUG("fired exp (-)") }
        |
        NOT K_Exp { $$ = new Not($2, yylineno); PRINTDEBUG("fired Not") }
        |
        K_Exp
        ;

K_Exp:
        K_Exp DOT LENGTH { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exp dot length\n") }
        |
        K_Exp DOT ID OPARANTHESIS ExpList EPARANTHESIS { $$ = new Call($1, new Identifier($3), $5, yylineno); 
        PRINTDEBUG("(call exp)") }
        |
        L_Exp
        ;

L_Exp:
        ID Root_Exp DOT LENGTH { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exp length\n") }
        |
        Root_Exp
        ;
        
Root_Exp:  
        OPARANTHESIS Exp EPARANTHESIS { $$ = $2; PRINTDEBUG("fired (exp)") }
        |
        ID Index { PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX> exp id index\n") }
        |
        INTEGER_LITERAL { $$ = new IntegerLiteral($1); PRINTDEBUG("fired integer literal") }
        |
        TRUE { $$ = new True(); PRINTDEBUG("fired True") }
        |
        FALSE { $$ = new False(); PRINTDEBUG("fired False") }
        |
        Object
        ;  

Object:
        ID { $$ = new IdentifierExp($1); PRINTDEBUG("fired IdentExp") }
        |
        THIS { $$ = new This(); PRINTDEBUG("fired This") }
        |
        NEW ID OPARANTHESIS EPARANTHESIS { $$ = new NewObject(new Identifier($2)); PRINTDEBUG("fired exp new id()") }
        |
        NEW PrimeType Index { $$ = new NewArray($3); PRINTDEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX exp new object prime\n") }
        ;

ExpList:
        Exp ExpRestList { $$ = $2; $$->push_back($1); PRINTDEBUG("exp list expr") } 
        | { $$ = new std::list<Exp *>(); PRINTDEBUG("explist empty, creating dummy list") }
        ;

ExpRest:
        COMMA Exp { $$ = $2; }
        ;

ExpRestList:
        ExpRestList ExpRest { $$ = $1; $$->push_back($2); PRINTDEBUG("(exprestlist loaded)") }  
        | { $$ = new std::list<Exp *>(); PRINTDEBUG("(explist finsished)") }  
        ;

%%
