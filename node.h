#include <list>
#include <string>
#include <map>
#include <iostream>

//enum std::string { Integer, Array, Boolean, Object };

/*******************    IDENTIFIER CLASS    *********************/
class Identifier {
protected:
    std::string id;
public:
    Identifier(const std::string str);
    std::string toString();
};

/*******************    EXP CLASS    ****************************/
/* Exp Abstract-Class */
class Exp {
public:
    virtual std::string visit() = 0;
};

/* Exp Sub-Classes */
class And : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
    int lineno;
public:
    And(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class Or : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
    int lineno;
public:
    Or(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class Is : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
    int lineno;
public:
    Is(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class IsNot : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
    int lineno;
public:
    IsNot(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class LessThan : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    LessThan(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class LessThanEqual : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    LessThanEqual(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class GreaterThan : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    GreaterThan(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class GreaterThanEqual : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    GreaterThanEqual(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class Plus : public Exp {
protected:
    Exp *lhs;
    Exp *rhs;
    int lineno;
public:
    Plus(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class Minus : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    Minus(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class Times : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    Times(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class Div : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    Div(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class ArrayLookup : public Exp {
protected:
    Exp * lhs;
    Exp * rhs;
    int lineno;
public:
    ArrayLookup(Exp *lhs, Exp *rhs, int lineno);
    std::string visit();
};

class ArrayLength : public Exp {
protected:
    Exp * e;
public:
    ArrayLength(Exp *e);
    std::string visit();
};

class Call : public Exp {
protected:
    Exp * e;
    Identifier * i;
    std::list<Exp *> * el;
public:
    Call(Exp *e, Identifier *i, std::list<Exp *> *el);
    std::string visit();
};

class IntegerLiteral : public Exp {
protected:
    int num;
public:
    IntegerLiteral(int i);
    std::string visit();
};

class True : public Exp {
public:
    True() {}
    std::string visit();
};

class False : public Exp {
public:
    False() {}
    std::string visit();
};

class IdentifierExp : public Exp {
protected:
    std::string id;
public:
    IdentifierExp(std::string str);
    std::string visit();
};

class This : public Exp {
public:
    This() {}
    std::string visit();
};

class NewArray : public Exp {
protected:
    Exp * e;
public:
    NewArray(Exp *e);
    std::string visit();
};

class NewObject : public Exp {
protected:
    Identifier * i;
public:
    NewObject(Identifier *i);
    std::string visit();
};

class Not : public Exp {
protected:
    Exp * e;
    int lineno;
public:
    Not(Exp *e, int lineno);
    std::string visit();
};

class NegativeExp : public Exp {
protected:
    Exp * e;
    int lineno;
public:
    NegativeExp(Exp *e, int lineno);
    std::string visit();
};

class PositiveExp : public Exp {
protected:
    Exp * e;
    int lineno;
public:
    PositiveExp(Exp *e, int lineno);
    std::string visit();
};


/*******************    STATEMENT CLASS    ****************************/
//abstract Statement class
class Statement {
public:
    virtual void visit() = 0;
};

class Block : public Statement {
protected:
    std::list<Statement *> *sl;
public:
    Block(std::list<Statement *> *sl);
    void visit();
};

class If : public Statement {
protected:
    Exp *e;
    Statement *s1;
    Statement *s2;
    int lineno;

public:
    If(Exp *e, Statement *s1, Statement *s2, int lineno);
    void visit();
};

class While : public Statement {
protected:
    Exp *e;
    Statement *s;
    int lineno;

public:
    While(Exp *e, Statement *s, int lineno);
    void visit();
};

class Print : public Statement {
protected:    
    Exp *e;
    int lineno;

public:
    Print(Exp *e, int lineno);
    void visit();
};

class Println : public Statement {
protected:    
    Exp *e;
    int lineno;

public:
    Println(Exp *e, int lineno);
    void visit();
};

class PrintString : public Statement {
protected:    
    const std::string str;
public:
    PrintString(const std::string str);
    void visit();
};

class PrintStringln : public Statement {
protected:    
    const std::string str;
public:
    PrintStringln(const std::string str);
    void visit();
};

class Assign : public Statement {
protected:
    Identifier *i;
    Exp *e;
    int lineno;

public:
    Assign(Identifier *i, Exp *e, int lineno);
    void visit();
};

class ArrayAssign : public Statement {
protected:
    Identifier *i;
    Exp * e1;
    Exp * e2;
public:
   ArrayAssign(Identifier *i, Exp *e1, Exp *e2);
   void visit();
};

/*******************    TYPE CLASS    ****************************/
class Type {
public:
    virtual std::string getType() = 0;
};

class IntArrayType : public Type {
public:
    IntArrayType() {}
    std::string getType();
};

class BooleanType : public Type {
public:    
    BooleanType() {}
    std::string getType();
};

class IntegerType : public Type {
public:
    IntegerType() {}
    std::string getType();
};

class IdentifierType : public Type {  
protected:
    std::string str;
public:
    IdentifierType(const std::string s);
    std::string getType();
};

/*******************    VAR CLASS    ****************************/
class VarDecl {
public:
    Type *t;
    Identifier *i;
    VarDecl(Type *t, Identifier *i);
    void visit();
};

/*******************    FORMAL CLASS    ****************************/
class Formal {
public:
    Type *t;
    Identifier *i;
    Formal(Type *t, Identifier *i);
    void visit();
};

/*******************    METHOD CLASS    ****************************/
class MethodDecl {
protected:
    Type *t;
    std::list<Formal *> *fl;
    std::list<VarDecl *> *vl;
    std::list<Statement *> *sl;
    Exp *e;
    int lineno;

    std::map<std::string, VarDecl *> localVariables;
    std::map<std::string, Formal *> parameters;

public:
    Identifier *i;
    MethodDecl(Type *t, Identifier *i, std::list<Formal *> *fl, std::list<VarDecl *> *vl, std::list<Statement *> *sl, Exp *e, int lineno);
    void visit();
};


/*******************    CLASS DECLARATION CLASS ****************************/
//abstract class
class ClassDecl {
public:
    virtual void visit() = 0;
    virtual std::string getName() = 0;
    std::map<std::string, VarDecl *> fieldVariables;
    std::map<std::string, MethodDecl *> methods;
};

class ClassDeclSimple : public ClassDecl {
protected:
    Identifier *i;
    std::list<VarDecl *> *vl;
    std::list<MethodDecl *> *ml;
    int lineno;

public:
    ClassDeclSimple(Identifier *i, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml, int lineno);
    void visit();
    std::string getName();
};

class ClassDeclExtends : public ClassDecl { 
protected:
    Identifier *i;
    Identifier *j;
    std::list<VarDecl *> *vl;
    std::list<MethodDecl *> *ml;
    int lineno;

public:
    ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml, int lineno);
    void visit();
    std::string getName();
};

/*******************    MAIN CLASS    ****************************/
class MainClass {
protected:
    Identifier *i2;
    Statement *s;

public:
    Identifier *i1;
    MainClass(Identifier *i1, Identifier *i2, Statement *s);
    void visit();
};

/*******************    PROGRAM CLASS ****************************/
class Program {
protected:
    MainClass *m;
    std::list<ClassDecl *> *cl;
    int lineno;

public:
    Program(MainClass *m, std::list<ClassDecl *> *cl, int lineno);
    void visit();
};

extern std::map<std::string, int> varTable;
extern std::map<std::string, ClassDecl *> classTable;
extern Program *root;
