CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison
YFLAGS= -v -y -d -g -t --debug

RM = /bin/rm -f

parser: y.tab.o lex.yy.o node.o
	${CCC} -o parser lex.yy.o y.tab.o node.o

node.o: node.cpp node.h
	${CCC} -c node.cpp
y.tab.o: parser.y
	${YACC} ${YFLAGS} parser.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: parser.l
	${LEX} $(LFLAGS) parser.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o exp
