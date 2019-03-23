#include <vector>
#include <string>
#include <iostream>

class ClassDecl;
class Exp;
class Formal;
class MethodDecl;
class Statement;
class VarDecl;

typedef std::vector<ClassDecl *> ClassDeclList;
typedef std::vector<Exp *> ExpList;
typedef std::vector<Formal *> FormalList;
typedef std::vector<MethodDecl *> MethodDeclList;
typedef std::vector<Statement *> StatementList;
typedef std::vector<VarDecl *> VarDeclList;

/*******************    IDENTIFIER CLASS    ****************************/
class Identifier {
protected:
    std::string id;
public:
    Identifier(std::string str);
};

/*******************    EXP CLASS    ****************************/
/* Exp Abstract-Class */
class Exp {

};

/* Exp Sub-Classes */
class And : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
public:
    And(Exp *left, Exp *right);
};

class LessThan : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    LessThan(Exp *e1, Exp *e2);
};

class Plus : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
public:
    Plus(Exp *e1, Exp *e2);
};

class Minus : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    Minus(Exp *e1, Exp *e2);
};

class Times : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    Times(Exp *e1, Exp *e2);
};

class ArrayLookup : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    ArrayLookup(Exp *e1, Exp *e2);
};

class ArrayLength : public Exp {
protected:
    Exp * e;
public:
    ArrayLength(Exp *e);
};

class Call : public Exp {
protected:
    Exp * e;
    Identifier * i;
    ExpList * el;
public:
    Call(Exp *e, Identifier *i, ExpList *el);
};

class IntegerLiteral : public Exp {
protected:
    int num;
public:
    IntegerLiteral(int i);
};

class True : public Exp {
public:
    True() {}
};

class False : public Exp {
public:
    False() {}
};

class IdentifierExp : public Exp {
protected:
    std::string id;
public:
    IdentifierExp(std::string str);
};

class This : public Exp {
public:
    This() {}
};

class NewArray : public Exp {
protected:
    Exp * e;
public:
    NewArray(Exp *e);
};

class NewObject : public Exp {
protected:
    Identifier * i;
public:
    NewObject(Identifier *i);
};

class Not : public Exp {
protected:
    Exp * e;
public:
    Not(Exp *e);
};

class NegativeExp : public Exp {
protected:
    Exp * e;
public:
    NegativeExp(Exp *e);
};

class PositiveExp : public Exp {
protected:
    Exp * e;
public:
    PositiveExp(Exp *e);
};


/*******************    STATEMENT CLASS    ****************************/
//abstract Statement class
class Statement {

};

class Block : public Statement {
protected:
    StatementList sl;
public:
    Block(StatementList sl);
};

class If : public Statement {
protected:
    Exp *e;
    Statement *s1;
    Statement *s2;

public:
    If(Exp *e, Statement *s1, Statement *s2);
};

class While : public Statement {
protected:
    Exp *e;
    Statement *s;
public:
    While(Exp *e, Statement *s);
};

class Print : public Statement {
protected:    
    Exp *e;
public:
    Print(Exp *e);
};

class Assign : public Statement {
protected:
    Identifier *i;
    Exp *e;
public:
    Assign(Identifier *i, Exp *e);
};

class ArrayAssign : public Statement {
protected:
    Identifier *i;
    Exp * e1;
    Exp * e2;
public:
   ArrayAssign(Identifier *i, Exp *e1, Exp *e2);
};

/*******************    TYPE CLASS    ****************************/
//abstract class
class Type {

};
class IntArrayType : public Type {
public:
    IntArrayType() {}
};

class BooleanType : public Type {
public:    
    BooleanType() {}
};

class IntegerType : public Type {
public:
    IntegerType() {}
};

class IdentifierType : public Type {  
protected:
    std::string str;
public:
    IdentifierType(const std::string s);
};

/*******************    VAR CLASS    ****************************/
class VarDecl {
protected:
    Type *t;
    Identifier *i;
public:
    VarDecl(Type *t, Identifier *i);
};

/*******************    METHOD CLASS    ****************************/
class MethodDecl {
protected:
    Type *t;
    Identifier *i;
    FormalList *fl;
    VarDeclList *vl;
    StatementList *sl;
    Exp *e;

public:
    MethodDecl(Type *t, Identifier *i, FormalList *fl, VarDeclList *vl, StatementList *sl, Exp *e);
};

/*******************    FORMAL CLASS    ****************************/
class Formal {
protected:
    Type *t;
    Identifier *i;
public:
    Formal(Type *t, Identifier *i);
};

/*******************    CLASS DECLARATION CLASS ****************************/
//abstract class
class ClassDecl {

};

class ClassDeclSimple : public ClassDecl {
protected:
    Identifier *i;
    VarDeclList *vl;
    MethodDeclList *ml;

public:
    ClassDeclSimple(Identifier *i, VarDeclList *vl, MethodDeclList *ml);
};

class ClassDeclExtends : public ClassDecl { 
protected:
    Identifier *i;
    Identifier *j;
    VarDeclList *vl;
    MethodDeclList *ml;

public:
    ClassDeclExtends(Identifier *i, Identifier *j, VarDeclList *vl, MethodDeclList *ml);
};

/*******************    MAIN CLASS    ****************************/
class MainClass {
protected:
    Identifier *i1;
    Identifier *i2;
public:
    
    /*Statement s;

    MainClass(Identifier i1, Identifier i2, Statement s) :
        i1(i1),
        i2(i2),
        s(s) {std::cout << "ouch";}
    */  
    MainClass(Identifier *i1, Identifier *i2); 
};

/*******************    PROGRAM CLASS ****************************/
class Program {
protected:
    MainClass *m;
    ClassDeclList *cl;
public:
    Program(MainClass *m, ClassDeclList *cl);
};

extern Program *root;
