# MiniJava Compiler

This is an ARM Assembly Compiler interpretation for the MiniJava Language, a subset of Java by Oracle. The meaning of a MiniJava program is given by its meaning as a Java program. Overloading is not allowed in MiniJava. 

## Usage
#### To Clone the Repository
```
$ git clone https://github.com/addisonpolcyn/MiniJava-Compiler.git
```
#### Setup
```
$ make
```
#### Cleaning
```
$ make clean
```
#### Compiling Minijava to ARM Assembly
This will type check, analyze, compile, and produce an ARM Assembly Equivalent file as output.
```
$ mjavac factorial.java
```
#### Running an ARM Assembly file
Not every machine supports ARM Assembly by default. Raspberry Pi does support it. The ARM Assembly file must be assembled and then executed to see proper output.

## Sample MiniJava Program
```Java
class Factorial{
    public static void main(String[] a){
	System.out.println(new Fac().ComputeFac(10));
    }
}

class Fac {

    public int ComputeFac(int num){
	int num_aux ;
	if (num < 1)
	    num_aux = 1 ;
	else 
	    num_aux = num * (this.ComputeFac(num-1)) ;
	return num_aux ;
    }

}
```

## Technology Used
One or more of the technologies below may need to be installed during setup.
- C
- C++ 
- Flex
- Bison
- ARM Assembly
## MiniJava Grammar
Program ::= [MainClass](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod2)  (  [ClassDeclaration](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod3)  )* <EOF>

MainClass ::= "class"  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  "{" "public" "static" "void" "main" "(" "String" "[" "]"  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  ")" "{"  [Statement](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod5)  "}" "}"

ClassDeclaration ::= "class"  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  ( "extends"  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  )? "{" (  [VarDeclaration](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod6)  )* (  [MethodDeclaration](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod7)  )* "}"

VarDeclaration ::= [Type](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod8)  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  ";"

MethodDeclaration ::= "public"  [Type](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod8)  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  "(" (  [Type](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod8)  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  ( ","  [Type](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod8)  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  )* )? ")" "{" (  [VarDeclaration](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod6)  )* (  [Statement](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod5)  )* "return"  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ";" "}"

Type ::= "int" "[" "]" 
|
"boolean"
|
"int"
|
[Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)

Statement ::= "{" (  [Statement](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod5)  )* "}"
|
"if" "("  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ")"  [Statement](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod5)  "else"  [Statement](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod5)
|
"while" "("  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ")"  [Statement](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod5)
|
"System.out.println" "("  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ")" ";"
|
[Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  "="  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ";"
|
[Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  "["  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  "]" "="  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ";"

Expression ::= [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ( "&&" | "<" | "+" | "-" | "*" )  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)
|
[Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  "["  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  "]"
|
[Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  "." "length"
|
[Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  "."  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  "(" (  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ( ","  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  )* )? ")"
|
INTEGER_LITERAL
|
"true"
|
"false"
|
[Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)
|
"this"
|
"new" "int" "["  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  "]"
|
"new"  [Identifier](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod4)  "(" ")"
|
"!"  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)
|
"("  [Expression](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html#prod9)  ")"

Identifier ::= IDENTIFIER

> **Note:** These MiniJava grammar rules are from [http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html](http://www.cs.tufts.edu/~sguyer/classes/comp181-2006/minijava.html) and may be share or not share similarities with this MiniJava Compiler. 
