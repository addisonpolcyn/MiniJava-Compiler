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

void And::evaluate() {
    std::cout << "(And)" << std::endl;
}

void LessThan::evaluate() {
    std::cout << "(LessThan)" << std::endl;
}

void Plus::evaluate() {
    std::cout << "(Plus)" << std::endl;
}

void Minus::evaluate() {
    std::cout << "(Minus)" << std::endl;
}

void Times::evaluate() {
    std::cout << "(Times)" << std::endl;
}

void ArrayLookup::evaluate() {
    std::cout << "(ArrayLookup)" << std::endl;
}

void ArrayLength::evaluate() {
    std::cout << "(ArrLength)" << std::endl;
}

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

void IdentifierExp::evaluate() {
    std::cout << "(IdentifierExp)" << std::endl;
}

void This::evaluate() {
    std::cout << "(This)" << std::endl;
}

void NewArray::evaluate() {
    std::cout << "(NewArray)" << std::endl;
}

void NewObject::evaluate() {
    std::cout << "(NewObject)" << std::endl;
}

void Not::evaluate() {
    std::cout << "(Not)" << std::endl;
}

void NegativeExp::evaluate() {
    std::cout << "(NegativeExp)" << std::endl;
}

void PositiveExp::evaluate() {
    std::cout << "(PositiveExp)" << std::endl;
}

/*******************    STATEMENT CLASS    ****************************/
void Block::evaluate() {
    std::cout << "(evaluate)" << std::endl;
}

void If::evaluate() {
    std::cout << "(If)" << std::endl;
}

void While::evaluate() {
    std::cout << "(While)" << std::endl;
}

Print::Print(Exp *e): e(e) {}
void Print::evaluate() {
    e->evaluate();
    std::cout << "(Print)" << std::endl;
}

void Assign::evaluate() {
    std::cout << "(Assign)" << std::endl;
}

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
void ClassDeclSimple::evaluate() {
    std::cout << "(ClassDeclSimple)" << std::endl;
}

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
