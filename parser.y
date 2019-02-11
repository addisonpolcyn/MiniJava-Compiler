%{
#include <stdio.h>
#include <string.h>

FILE *yyin;
 
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 
  
/*main()
{
        yyparse();
} */

int main(int argc, char **argv) {
    /* Process command line args*/
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
