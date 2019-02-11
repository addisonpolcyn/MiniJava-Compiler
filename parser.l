%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
    /* Declarations */
class {
    printf("CLASS");
}
public {
    printf("PUBLIC");
}
static {
    printf("STATIC");
}
void {
    printf("VOID");
}
main {
    printf("MAIN");
}
extends {
    printf("EXTENDS");
}
return {
    printf("RETURN");
}

    /* Functions */
Length {
    printf("LENGTH");
}
System.out.println {
    printf("PRINT");
}
    
    /* Objects */
this {
    printf("THIS");
}
new {
    printf("NEW");
}

    /* Loops and if-statements */
if {
    printf("IF");
}
else {
    printf("ELSE");
}
while {
    printf("WHILE");
}

    /* booleans */
true {
    printf("TRUE");
}
false {
    printf("FALSE");
}

    /* Operators */
= {
    printf("EQUAL");
}
\+ {
    printf("PLUS");
}
- {
    printf("MINUS");
}
! {
    printf("NOT");
}
"." {
    printf("DOT");
}

    /* Separators */
, {
    printf("COMMA");
}
; {
    printf("SEMICOLON");
}
\( {
    printf("OPARANTHESIS");
}
\) {
    printf("EPARANTHESIS");
}
"\[" {
    printf("OBRACK");
}
"\]" {
    printf("EBRACK");
}
\{ {
    printf("OBRACE");
}
\} {
    printf("EBRACE");
}
\" {
    printf("QUOTE");
}

    /* Null Grammar */
[0-9]+ {
    yylval=atoi(yytext);
    printf("INTEGER_LITERAL");
    //return INTEGER_LITERAL;
}
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
\n {
    /* ignore end of line */
    yylineno++;
}
[ \t]+ { 
    /* ignore whitespace */
}
%%
