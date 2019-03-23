#include <list>
#include <string>
#include <iostream>

/*******************    IDENTIFIER CLASS    *********************/
class Identifier {
protected:
    std::string id;
public:
    Identifier(std::string str) {
        id=str;
    }
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
    And(Exp *left, Exp *right) {
        lhs=left;
        rhs=right;
    }
};

class LessThan : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    LessThan(Exp *e1, Exp *e2) {
        lhs=e1;
        rhs=e2;
    }
};

class Plus : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
public:
    Plus(Exp *e1, Exp *e2) {
        lhs = (e1);
        rhs = (e2); 
    }
};

class Minus : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    Minus(Exp *e1, Exp *e2){
        lhs=e1;
        rhs=e2;
    }
};

class Times : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    Times(Exp *e1, Exp *e2) {
        lhs=e1;
        rhs=e2;
    }
};

class ArrayLookup : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    ArrayLookup(Exp *e1, Exp *e2) {
        lhs=e1;
        rhs=e2;
    }
};

class ArrayLength : public Exp {
protected:
    Exp * e;
public:
    ArrayLength(Exp *e) {
        e=e;
    }
};

class Call : public Exp {
protected:
    Exp * e;
    Identifier * i;
    std::list<Exp *> * el;
public:
    Call(Exp *e, Identifier *i, std::list<Exp *> *el) {
        e=e;
        i=i;
        el=el;
    }
};

class IntegerLiteral : public Exp {
protected:
    int num;
public:
    IntegerLiteral(int i) {
        num=i;
    }
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
    IdentifierExp(std::string str) {
        id=str;
    }
};

class This : public Exp {
public:
    This() {}
};

class NewArray : public Exp {
protected:
    Exp * e;
public:
    NewArray(Exp *e) {
        e=e;
    }
};

class NewObject : public Exp {
protected:
    Identifier * i;
public:
    NewObject(Identifier *i) {
        i=i;
    }
};

class Not : public Exp {
protected:
    Exp * e;
public:
    Not(Exp *e) {
        e=e;
    }
};

class NegativeExp : public Exp {
protected:
    Exp * e;
public:
    NegativeExp(Exp *e) {
        e=e;
    }
};

class PositiveExp : public Exp {
protected:
    Exp * e;
public:
    PositiveExp(Exp *e) { 
        e=e;
    }
};


/*******************    STATEMENT CLASS    ****************************/
//abstract Statement class
class Statement {

};

class Block : public Statement {
protected:
    std::list<Statement *> *sl;
public:
    Block(std::list<Statement *> *sl) {
        sl=sl;
    }
};

class If : public Statement {
protected:
    Exp *e;
    Statement *s1;
    Statement *s2;

public:
    If(Exp *e, Statement *s1, Statement *s2) {
        e=e;
        s1=s1;
        s2=s2;
    }
};

class While : public Statement {
protected:
    Exp *e;
    Statement *s;
public:
    While(Exp *e, Statement *s) {
        e=e;
        s=s;
    }
};

class Print : public Statement {
protected:    
    Exp *e;
public:
    Print(Exp *e) {
        e=e;
    }
};

class Assign : public Statement {
protected:
    Identifier *i;
    Exp *e;
public:
    Assign(Identifier *i, Exp *e) {
        i=i;
        e=e;
    }
};

class ArrayAssign : public Statement {
protected:
    Identifier *i;
    Exp * e1;
    Exp * e2;
public:
   ArrayAssign(Identifier *i, Exp *e1, Exp *e2) {
    i=i;
    e1=e1;
    e2=e2;
   }
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
    IdentifierType(const std::string s) {
        str=s;
    }
};

/*******************    VAR CLASS    ****************************/
class VarDecl {
protected:
    Type *t;
    Identifier *i;
public:
    VarDecl(Type *t, Identifier *i) {
        t=t;
        i=i;
    }
};

/*******************    FORMAL CLASS    ****************************/
class Formal {
protected:
    Type *t;
    Identifier *i;
public:
    Formal(Type *t, Identifier *i) {
        t=t;
        i=i;
    }
};

/*******************    METHOD CLASS    ****************************/
class MethodDecl {
protected:
    Type *t;
    Identifier *i;
    std::list<Formal *> *fl;
    std::list<VarDecl *> *vl;
    std::list<Statement *> *sl;
    Exp *e;

public:
    MethodDecl(Type *t, Identifier *i, std::list<Formal *> *fl, std::list<VarDecl *> *vl, std::list<Statement *> *sl, Exp *e) {
        t=t;
        i=i;
        fl=fl;
        vl=vl;
        sl=sl;
        e=e;
    }
};


/*******************    CLASS DECLARATION CLASS ****************************/
//abstract class
class ClassDecl {

};

class ClassDeclSimple : public ClassDecl {
protected:
    Identifier *i;
    std::list<VarDecl *> *vl;
    std::list<MethodDecl *> *ml;

public:
    ClassDeclSimple(Identifier *i, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml) {
        i=i;
        vl=vl;
        ml=ml;
    }
};

class ClassDeclExtends : public ClassDecl { 
protected:
    Identifier *i;
    Identifier *j;
    std::list<VarDecl *> *vl;
    std::list<MethodDecl *> *ml;

public:
    ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml) {
        i=i;
        j=j;
        vl=vl;
        ml=ml;
    }
};

/*******************    MAIN CLASS    ****************************/
class MainClass {
protected:
    Identifier *i1;
    Identifier *i2;
    Statement *s;

public:
    MainClass(Identifier *i1, Identifier *i2, Statement *s) {
        i1=i1;
        i2=i2;
        s=s;
    }
};

/*******************    PROGRAM CLASS ****************************/
class Program {
protected:
    MainClass *m;
    std::list<ClassDecl *> *cl;
public:
    Program(MainClass *m, std::list<ClassDecl *> *cl) {
        m=m;
        cl=cl;
    }
};

extern Program *root;
