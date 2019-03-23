#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include "node.h"

/*******************    IDENTIFIER CLASS    *********************/
Identifier::Identifier(const std::string str): id(str) {}
void Identifier::evaluate() {
    std::cout << "Identifier:" << id << std::endl;
}

/*******************    EXP SUB-CLASSES    ****************************/
And::And(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int And::evaluate() {
    std::cout << "(And)" << std::endl;
    return 0;
}

LessThan::LessThan(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int LessThan::evaluate() {
    std::cout << "(LessThan)" << std::endl;
    return 0;
}

Plus::Plus(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Plus::evaluate() {
    std::cout << "(Plus)" << std::endl;
    return 0;
}

Minus::Minus(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Minus::evaluate() {
    std::cout << "(Minus)" << std::endl;
    return 0;
}

Times::Times(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Times::evaluate() {
    std::cout << "(Times)" << std::endl;
    return 0;
}

ArrayLookup::ArrayLookup(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int ArrayLookup::evaluate() {
    std::cout << "(ArrayLookup)" << std::endl;
    return 0;
}

ArrayLength::ArrayLength(Exp *e): e(e) {}
int ArrayLength::evaluate() {
    std::cout << "(ArrLength)" << std::endl;
    return 0;
}

Call::Call(Exp *e, Identifier *i, std::list<Exp *> *el): e(e), i(i), el(el) {}
int Call::evaluate() {
    std::cout << "(Call)" << std::endl;
    return 0;
}

IntegerLiteral::IntegerLiteral(int i): num(i) {}
int IntegerLiteral::evaluate() {
    std::cout << "(IntegerLiteral)" << std::endl;
    return num;
}

int True::evaluate() {
    std::cout << "(True)" << std::endl;
    return 0;
}

int False::evaluate() {
    std::cout << "(False)" << std::endl;
    return 0;
}

int This::evaluate() {
    std::cout << "(This)" << std::endl;
    return 0;
}

IdentifierExp::IdentifierExp(std::string str): id(str) {}
int IdentifierExp::evaluate() {
    std::cout << "(IdentifierExp)" << std::endl;
    return 0;
}

NewArray::NewArray(Exp *e): e(e) {}
int NewArray::evaluate() {
    std::cout << "(NewArray)" << std::endl;
    return 0;
}

NewObject::NewObject(Identifier *i): i(i) {}
int NewObject::evaluate() {
    std::cout << "(NewObject)" << std::endl;
    return 0;
}

Not::Not(Exp *e): e(e) {}
int Not::evaluate() {
    std::cout << "(Not)" << std::endl;
    return 0;
}

NegativeExp::NegativeExp(Exp *e): e(e) {}
int NegativeExp::evaluate() {
    std::cout << "(NegativeExp)" << std::endl;
    return 0;
}

PositiveExp::PositiveExp(Exp *e): e(e) {}
int PositiveExp::evaluate() {
    std::cout << "(PositiveExp)" << std::endl;
    return 0;
}

/*******************    STATEMENT CLASS    ****************************/
Block::Block(std::list<Statement *> *sl): sl(sl) {}
void Block::evaluate() {
    std::cout << "(evaluate)" << std::endl;
}

If::If(Exp *e, Statement *s1, Statement *s2): e(e), s1(s1), s2(s2) {}
void If::evaluate() {
    std::cout << "(If)" << std::endl;
}

While::While(Exp *e, Statement *s): e(e), s(s) {} 
void While::evaluate() {
    std::cout << "(While)" << std::endl;
}

Print::Print(Exp *e): e(e) {}
void Print::evaluate() {
    int num = e->evaluate();
    std::cout << "(Print):";
    std::cout << num;
}

Println::Println(Exp *e): e(e) {}
void Println::evaluate() {
    int num = e->evaluate();
    std::cout << "(Println):\n";
    std::cout << num << std::endl;
}

PrintString::PrintString(std::string str): str(str) {}
void PrintString::evaluate() {
    std::cout << "(PrintString):" << str <<std::endl;
    std::string s(str);
    std::cout << str;
}

PrintStringln::PrintStringln(const std::string str): str(str) {}
void PrintStringln::evaluate() {
    std::cout << "(PrintStringln):" << str << std::endl;
    std::cout << str << std::endl;
}

Assign::Assign(Identifier *i, Exp *e): i(i), e(e) {}
void Assign::evaluate() {
    std::cout << "(Assign)" << std::endl;
}
ArrayAssign::ArrayAssign(Identifier *i, Exp *e1, Exp *e2): i(i), e1(e1), e2(e2) {}
void ArrayAssign::evaluate() {
    std::cout << "(ArrayAssign)" << std::endl;
}

/*******************    TYPE CLASS    ****************************/
void IntArrayType::evaluate() {
    std::cout << "(IntArrayType)" << std::endl;
}

void BooleanType::evaluate() {
    std::cout << "(BooleanType)" << std::endl;
}

void IntegerType::evaluate() {
    std::cout << "(IntegerType)" << std::endl;
}

void IdentifierType::evaluate() {
    std::cout << "(IdentifierType)" << std::endl;
}

/*******************    VAR CLASS    ****************************/
/*
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
*/
/*******************    FORMAL CLASS    ****************************/
/*
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
*/
/*******************    METHOD CLASS    ****************************/
/*
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

*/
/******************    CLASS DECLARATION SUB-CLASS    ************/
ClassDeclSimple::ClassDeclSimple(Identifier *i, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml): i(i), vl(vl), ml(ml) {}
void ClassDeclSimple::evaluate() {
    std::cout << "(ClassDeclSimple)" << std::endl;
}

ClassDeclExtends::ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml): i(i), j(j), vl(vl), ml(ml) {}
void ClassDeclExtends::evaluate() {
    std::cout << "(ClassDeclExtends)" << std::endl;
}

/*******************    MAIN CLASS    ****************************/
MainClass::MainClass(Identifier *i1, Identifier *i2, Statement *s): i1(i1), i2(i2), s(s) {}
void MainClass::evaluate() {
    //evaluate Identifiers
    i1->evaluate();
    i2->evaluate();

    //evaluate Statement
    s->evaluate();
    
    std::cout << "(MainClass)" << std::endl;
};

/*******************    PROGRAM CLASS ****************************/
Program::Program(MainClass *m, std::list<ClassDecl *> *cl): m(m), cl(cl) {}
void Program::evaluate() {
    std::cout << "\n^ (Program Start)...\n" << std::endl;
    
    //evaluate ClassDeclarations
    std::list<ClassDecl *>::iterator classDeclIter;
    std::cout << "^btfn (Program Start)" << std::endl;
    for(classDeclIter = cl->begin(); classDeclIter != cl->end(); classDeclIter++){
        std::cout << "^agg (Program Start)" << std::endl;
        (*classDeclIter)->evaluate();
    std::cout << "^csces (Program Start)" << std::endl;
    }

    //evaluate MainClass    
    m->evaluate();
    
    std::cout << "\n...(Program End) $" << std::endl;
};
