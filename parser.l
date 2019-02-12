%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#define PRINTDEBUG(x) fprintf(stderr, "\n%s\n", (x)); // comment out print statement to remove the printing
%}

%option yylineno

%%


    /* Comments */
\/\/[^\n^\r]* {
    /* Single Comment */
    PRINTDEBUG(yytext)
}
"/*"([^*]|\*+[^/*])*\*+"/" {
    /* Multi-Comment */
    PRINTDEBUG(yytext)
}


    /* Declarations */
"class" {
    PRINTDEBUG(yytext)
    return CLASS;
}
"public" {
    PRINTDEBUG(yytext)
    return PUBLIC;
}
"static" {
    PRINTDEBUG(yytext)
    return STATIC;
}
"void" {
    PRINTDEBUG(yytext)
    return VOID;
}
"main" {
    PRINTDEBUG(yytext)
    return MAIN;
}
"extends" {
    PRINTDEBUG(yytext)
    return EXTENDS;
}
"return" {
    PRINTDEBUG(yytext)
    return RETURN;
}


    /* Functions */
".length" {
    PRINTDEBUG(yytext)
    return DOTLENGTH;
}
System.out.println {
    PRINTDEBUG(yytext)
    return PRINT;
}
   

    /* Objects */
this {
    PRINTDEBUG(yytext)
    return THIS;
}
new {
    PRINTDEBUG(yytext)
    return NEW;
}
"String" {
    PRINTDEBUG(yytext)
    return STRING;
}


    /* Primitive Types */
int {
    PRINTDEBUG(yytext)
    return INT;
}
boolean {
    PRINTDEBUG(yytext)
    return BOOL;
}


    /* Loops and if-statements */
if {
    PRINTDEBUG(yytext)
    return IF;
}
else {
    PRINTDEBUG(yytext)
    return ELSE;
}
while {
    PRINTDEBUG(yytext)
    return WHILE;
}


    /* booleans */
true {
    PRINTDEBUG(yytext)
    return TRUE;
}
false {
    PRINTDEBUG(yytext)
    return FALSE;
}


    /* Operators */
= {
    PRINTDEBUG(yytext)
    return EQUAL;
}
"++" {
    PRINTDEBUG(yytext)
    return PLUSPLUS;
}
! {
    PRINTDEBUG(yytext)
    return NOT;
}
"." {
    PRINTDEBUG(yytext)
    return DOT;
}


    /* Binary Operators */
&& {
    PRINTDEBUG(yytext)
    return AND;
}
"||" {
    PRINTDEBUG(yytext)
    return OR;
}
"<=" {
    PRINTDEBUG(yytext)
    return LESSTHANEQUAL;
}
">=" {
    PRINTDEBUG(yytext)
    return GREATERTHANEQUAL;
}
\< {
    PRINTDEBUG(yytext)
    return LESS;
}
\> {
    PRINTDEBUG(yytext)
    return GREATER;
}
"==" {
    PRINTDEBUG(yytext)
    return IS;
}
"!=" {
    PRINTDEBUG(yytext)
    return ISNOT;
}
\+ {
    PRINTDEBUG(yytext)
    return PLUS;
}
- {
    PRINTDEBUG(yytext)
    return MINUS;
}
\* {
    PRINTDEBUG(yytext)
    return TIMES;
}
\/ {
    PRINTDEBUG(yytext)
    return SLASH;
}


    /* Separators */
, {
    PRINTDEBUG(yytext)
    return COMMA;
}
; {
    PRINTDEBUG(yytext)
    return SEMICOLON;
}
\( {
    PRINTDEBUG(yytext)
    return OPARANTHESIS;
}
\) {
    PRINTDEBUG(yytext)
    return EPARANTHESIS;
}
"\[" {
    PRINTDEBUG(yytext)
    return OBRACK;
}
"\]" {
    PRINTDEBUG(yytext)
    return EBRACK;
}
\{ {
    PRINTDEBUG(yytext)
    return OBRACE;
}
\} {
    PRINTDEBUG(yytext)
    return EBRACE;
}
\" {
    PRINTDEBUG(yytext)
    return QUOTE;
}


    /* Variables */
[a-zA-Z][a-zA-Z0-9_]* {
    PRINTDEBUG(yytext)
    return ID;
}
[0-9]+ {
    PRINTDEBUG(yytext)
    yylval=atoi(yytext);
    return INTEGER_LITERAL;
}
\"[^\n^\r]*\" {
    PRINTDEBUG(yytext)
    return STRING_LITERAL;
}


    /* Null Grammar */
\n {
    PRINTDEBUG(yytext)
    /* ignore end of line */
}
[ \t]+ { 
    PRINTDEBUG(yytext)
    /* ignore whitespace */
}


    /*Garbage collection */
. {
    PRINTDEBUG(yytext)
    printf("garbage\n");
}


%%
