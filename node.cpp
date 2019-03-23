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
void And::evaluate() {
    std::cout << "(And)" << std::endl;
}

LessThan::LessThan(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
void LessThan::evaluate() {
    std::cout << "(LessThan)" << std::endl;
}

Plus::Plus(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
void Plus::evaluate() {
    std::cout << "(Plus)" << std::endl;
}

Minus::Minus(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
void Minus::evaluate() {
    std::cout << "(Minus)" << std::endl;
}

Times::Times(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
void Times::evaluate() {
    std::cout << "(Times)" << std::endl;
}

ArrayLookup::ArrayLookup(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
void ArrayLookup::evaluate() {
    std::cout << "(ArrayLookup)" << std::endl;
}

ArrayLength::ArrayLength(Exp *e): e(e) {}
void ArrayLength::evaluate() {
    std::cout << "(ArrLength)" << std::endl;
}

Call::Call(Exp *e, Identifier *i, std::list<Exp *> *el): e(e), i(i), el(el) {}
void Call::evaluate() {
    std::cout << "(Call)" << std::endl;
}

IntegerLiteral::IntegerLiteral(int i): num(i) {}
void IntegerLiteral::evaluate() {
    std::cout << "(IntegerLiteral)" << std::endl;
}

void True::evaluate() {
    std::cout << "(True)" << std::endl;
}

void False::evaluate() {
    std::cout << "(False)" << std::endl;
}

void This::evaluate() {
    std::cout << "(This)" << std::endl;
}

IdentifierExp::IdentifierExp(std::string str): id(str) {}
void IdentifierExp::evaluate() {
    std::cout << "(IdentifierExp)" << std::endl;
}

NewArray::NewArray(Exp *e): e(e) {}
void NewArray::evaluate() {
    std::cout << "(NewArray)" << std::endl;
}

NewObject::NewObject(Identifier *i): i(i) {}
void NewObject::evaluate() {
    std::cout << "(NewObject)" << std::endl;
}

Not::Not(Exp *e): e(e) {}
void Not::evaluate() {
    std::cout << "(Not)" << std::endl;
}

NegativeExp::NegativeExp(Exp *e): e(e) {}
void NegativeExp::evaluate() {
    std::cout << "(NegativeExp)" << std::endl;
}

PositiveExp::PositiveExp(Exp *e): e(e) {}
void PositiveExp::evaluate() {
    std::cout << "(PositiveExp)" << std::endl;
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
    e->evaluate();
    std::cout << "(Print)" << std::endl;
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
/*******************    CLASS DECLARATION CLASS ****************************/
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
Program::Program(MainClass *m, std::list<ClassDecl *> *cl): m(m), cl(cl) { std::cout << "built program\n";}
void Program::evaluate() {
    std::cout << "^ (Program Start)" << std::endl;
    
    //evaluate ClassDeclarations
    //std::list<ClassDecl *>::iterator classDeclIter;
    //std::cout << "^btfn (Program Start)" << std::endl;
    //for(classDeclIter = cl->begin(); classDeclIter != cl->end(); classDeclIter++){
      //  std::cout << "^agg (Program Start)" << std::endl;
        //(*classDeclIter)->evaluate();
    //std::cout << "^csces (Program Start)" << std::endl;
    //}

    //evaluate MainClass    
    m->evaluate();
    
    std::cout << "(Program End) $" << std::endl;
};
