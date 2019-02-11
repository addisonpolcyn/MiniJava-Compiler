%{
#include <stdio.h>
#include <string.h>

FILE *yyin;

extern int yylineno, yychar;
//void yyerror(const char *str)
yyerror(s)
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
%%
