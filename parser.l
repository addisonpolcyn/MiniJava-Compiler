%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
    /* Comments */
\/\/[^\n^\r]* {
    printf("SINGLE_COMMENT");
}
"/*"([^*]|\*+[^/*])*\*+"/" {
    printf("MULTI_COMMENT");
}

    /* Declarations */
"class" {
    printf("CLASS ");
    return CLASS;
}
"public" {
    printf("PUBLIC ");
    return PUBLIC;
}
"static" {
    printf("STATIC ");
    return STATIC;
}
"void" {
    printf("VOID ");
    return VOID;
}
"main" {
    printf("MAIN ");
    return MAIN;
}
"extends" {
    printf("EXTENDS ");
    return EXTENDS;
}
"return" {
    printf("RETURN ");
    return RETURN;
}

    /* Functions */
Length {
    printf("LENGTH ");
    return LENGTH;
}
System.out.println {
    printf("PRINT ");
    return PRINT;
}
    
    /* Objects */
this {
    printf("THIS ");
    return THIS;
}
new {
    printf("NEW ");
    return NEW;
}
"String" {
    printf("STRING ");
    return STRING;
}

    /* Primitive Types */
int {
    printf("INT ");
    return INT;
}
boolean {
    printf("BOOL");
    return BOOL;
}

    /* Loops and if-statements */
if {
    printf("IF ");
    return IF;
}
else {
    printf("ELSE ");
    return ELSE;
}
while {
    printf("WHILE ");
    return WHILE;
}

    /* booleans */
true {
    printf("TRUE ");
    return TRUE;
}
false {
    printf("FALSE ");
    return FALSE;
}

    /* Operators */
= {
    printf("EQUAL ");
    return EQUAL;
}
"++" {
    printf("PLUSPLUS ");
    return PLUSPLUS;
}
! {
    printf("NOT ");
    return NOT;
}
"." {
    printf("DOT ");
    return DOT;
}

    /* Binary Operators */
&& {
    printf("AND ");
    return AND;
}
"||" {
    printf("OR ");
    return OR;
}
\< {
    printf("LESS ");
    return LESS;
}
\> {
    printf("GREATER ");
    return GREATER;
}
"<=" {
    printf("LESSTHANEQUAL ");
    return LESSTHANEQUAL;
}
">=" {
    printf("GREATERTHANEQUAL ");
    return GREATERTHANEQUAL;
}
"==" {
    printf("IS ");
    return IS;
}
"!=" {
    printf("ISNOT ");
    return ISNOT;
}
\+ {
    printf("PLUS ");
    return PLUS;
}
- {
    printf("MINUS ");
    return MINUS;
}
\* {
    printf("TIMES ");
    return TIMES;
}
\/ {
    printf("SLASH ");
    return SLASH;
}


    /* Separators */
, {
    printf("COMMA ");
    return COMMA;
}
; {
    printf("SEMICOLON ");
    return SEMICOLON;
}
\( {
    printf("OPARANTHESIS ");
    return OPARANTHESIS;
}
\) {
    printf("EPARANTHESIS ");
    return EPARANTHESIS;
}
"\[" {
    printf("OBRACK ");
    return OBRACK;
}
"\]" {
    printf("EBRACK ");
    return EBRACK;
}
\{ {
    printf("OBRACE ");
    return OBRACE;
}
\} {
    printf("EBRACE ");
    return EBRACE;
}
\" {
    printf("QUOTE ");
    return QUOTE;
}

    /* heater grammar */
heat {
    return TOKHEAT;
}
on|off {
    yylval=!strcmp(yytext,"on");
    return STATE;
}
target {
    return TOKTARGET;
}
hotdog {
    printf("hotdog!\n");
}
temperature {
    return TOKTEMPERATURE;
}

    /* Variables */
[a-zA-Z][a-zA-Z0-9_]* {
    printf("ID ");
}
[0-9]+ {
    yylval=atoi(yytext);
    printf("INTEGER_LITERAL ");
}
\"[^\n^\r]*\" {
    printf("STRING_LITERAL ");
}

    /* Null Grammar */
\n {
    /* ignore end of line */
    printf("\n");
    yylineno++;
}
[ \t]+ { 
    /* ignore whitespace */
}

    /*Garbage collection */
. {
    printf("Err Uncaught String:%s\n",yytext);
}


%%
