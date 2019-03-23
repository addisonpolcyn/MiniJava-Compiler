#include <list>
#include <string>
#include <iostream>

/*******************    IDENTIFIER CLASS    *********************/
class Identifier {
protected:
    std::string id;
public:
    Identifier(const std::string str);
    void evaluate();
};

/*******************    EXP CLASS    ****************************/
/* Exp Abstract-Class */
class Exp {
public:
    virtual void evaluate() = 0;
};

/* Exp Sub-Classes */
class And : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
public:
    And(Exp *lhs, Exp *rhs);
    void evaluate();
};

class LessThan : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    LessThan(Exp *lhs, Exp *rhs);
    void evaluate();
};

class Plus : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
public:
    Plus(Exp *lhs, Exp *rhs);
    void evaluate();
};

class Minus : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    Minus(Exp *lhs, Exp *rhs);
    void evaluate();
};

class Times : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    Times(Exp *lhs, Exp *rhs);
    void evaluate();
};

class ArrayLookup : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
public:
    ArrayLookup(Exp *lhs, Exp *rhs);
    void evaluate();
};

class ArrayLength : public Exp {
protected:
    Exp * e;
public:
    ArrayLength(Exp *e);
    void evaluate();
};

class Call : public Exp {
protected:
    Exp * e;
    Identifier * i;
    std::list<Exp *> * el;
public:
    Call(Exp *e, Identifier *i, std::list<Exp *> *el);
    void evaluate();
};

class IntegerLiteral : public Exp {
protected:
    int num;
public:
    IntegerLiteral(int i);
    void evaluate();
};

class True : public Exp {
public:
    True() {}
    void evaluate();
};

class False : public Exp {
public:
    False() {}
    void evaluate();
};

class IdentifierExp : public Exp {
protected:
    std::string id;
public:
    IdentifierExp(std::string str);
    void evaluate();
};

class This : public Exp {
public:
    This() {}
    void evaluate();
};

class NewArray : public Exp {
protected:
    Exp * e;
public:
    NewArray(Exp *e);
    void evaluate();
};

class NewObject : public Exp {
protected:
    Identifier * i;
public:
    NewObject(Identifier *i);
    void evaluate();
};

class Not : public Exp {
protected:
    Exp * e;
public:
    Not(Exp *e);
    void evaluate();
};

class NegativeExp : public Exp {
protected:
    Exp * e;
public:
    NegativeExp(Exp *e);
    void evaluate();
};

class PositiveExp : public Exp {
protected:
    Exp * e;
public:
    PositiveExp(Exp *e);
    void evaluate();
};


/*******************    STATEMENT CLASS    ****************************/
//abstract Statement class
class Statement {
public:
    virtual void evaluate() = 0;
};

class Block : public Statement {
protected:
    std::list<Statement *> *sl;
public:
    Block(std::list<Statement *> *sl);
    void evaluate();
};

class If : public Statement {
protected:
    Exp *e;
    Statement *s1;
    Statement *s2;

public:
    If(Exp *e, Statement *s1, Statement *s2);
    void evaluate();
};

class While : public Statement {
protected:
    Exp *e;
    Statement *s;
public:
    While(Exp *e, Statement *s);
    void evaluate();
};

class Print : public Statement {
protected:    
    Exp *e;
public:
    Print(Exp *e);
    void evaluate();
};

class Assign : public Statement {
protected:
    Identifier *i;
    Exp *e;

public:
    Assign(Identifier *i, Exp *e);
    void evaluate();
};

class ArrayAssign : public Statement {
protected:
    Identifier *i;
    Exp * e1;
    Exp * e2;
public:
   ArrayAssign(Identifier *i, Exp *e1, Exp *e2);
   void evaluate();
};

/*******************    TYPE CLASS    ****************************/
class Type {
public:
    virtual void evaluate() = 0;
};
class IntArrayType : public Type {
public:
    IntArrayType() {}
    void evaluate();
};

class BooleanType : public Type {
public:    
    BooleanType() {}
    void evaluate();
};

class IntegerType : public Type {
public:
    IntegerType() {}
    void evaluate();
};

class IdentifierType : public Type {  
protected:
    std::string str;
public:
    IdentifierType(const std::string s) {
        str=s;
    }
    void evaluate();
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
    void evaluate();
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
    void evaluate();
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
    void evaluate();
};


/*******************    CLASS DECLARATION CLASS ****************************/
//abstract class
class ClassDecl {
public:
    virtual void evaluate() = 0;
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
    void evaluate();
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
    void evaluate();
};

/*******************    MAIN CLASS    ****************************/
class MainClass {
protected:
    Identifier *i1;
    Identifier *i2;
    Statement *s;

public:
    //MainClass(Identifier *i1, Identifier *i2, Statement *s):i1(i1), i2(i2), s(s) {
    
    //}
    MainClass(Identifier *i1, Identifier *i2, Statement *s);
    //:i1(i1), i2(i2), s(s) {
    void evaluate();
};

/*******************    PROGRAM CLASS ****************************/
class Program {
protected:
    MainClass *m;
    std::list<ClassDecl *> *cl;
public:
    /*Program(MainClass *m, std::list<ClassDecl *> *cl):m(m), cl(cl) {
        std::cout << "newprog-construct:"<< std::endl;
    }*/
    Program(MainClass *m, std::list<ClassDecl *> *cl);
    void evaluate();
};

extern Program *root;
