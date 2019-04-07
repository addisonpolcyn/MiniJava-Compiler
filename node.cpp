#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include "node.h"
#define PRINTDEBUG(x) std::cout << x;//fprintf(stdout, "\n%s\n", (x)); // comment out print statement to remove the printing

/*******************    IDENTIFIER CLASS    *********************/
Identifier::Identifier(const std::string str): id(str) {}
std::string Identifier::evaluate() {
    std::cout << "Identifier:" << id << std::endl;
    return id;
}

/*******************    EXP SUB-CLASSES    ****************************/
And::And(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int And::evaluate() {
    PRINTDEBUG("(And)");
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " && " << right << std::endl;
    return left && right;
}

Or::Or(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Or::evaluate() {
    PRINTDEBUG("(Or)");
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " || " << right << std::endl;
    return left || right;
}

Is::Is(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Is::evaluate() {
    PRINTDEBUG("(Is)");
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " == " << right << std::endl;
    return left == right;
}

IsNot::IsNot(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int IsNot::evaluate() {
    PRINTDEBUG("(IsNot)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " != " << right << std::endl;
    return left != right;
}

LessThan::LessThan(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int LessThan::evaluate() {
    PRINTDEBUG("(LessThan)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " < " << right << std::endl;
    return left < right;
}

LessThanEqual::LessThanEqual(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int LessThanEqual::evaluate() {
    PRINTDEBUG("LessThanEqual)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " <= " << right << std::endl;
    return left <= right;
}

GreaterThan::GreaterThan(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int GreaterThan::evaluate() {
    PRINTDEBUG("(GreaterThan)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " > " << right << std::endl;
    return left > right;
}

GreaterThanEqual::GreaterThanEqual(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int GreaterThanEqual::evaluate() {
    PRINTDEBUG("(GreaterThanEqual)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " >= " << right << std::endl;
    return left >= right;
}

Plus::Plus(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Plus::evaluate() {
    PRINTDEBUG("(Plus)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " + " << right << std::endl;
    return left + right;

}

Minus::Minus(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Minus::evaluate() {
    PRINTDEBUG("(Minus)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " - " << right << std::endl;
    return left - right;

}

Times::Times(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Times::evaluate() {
    PRINTDEBUG("(Times)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " * " << right << std::endl;
    return left * right;
}

Div::Div(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int Div::evaluate() {
    PRINTDEBUG("(Div)")
    int left = lhs->evaluate();
    int right = rhs->evaluate();
    
    std::cout << left << " / " << right << std::endl;
    return left / right;
}

ArrayLookup::ArrayLookup(Exp *lhs, Exp *rhs): lhs(lhs), rhs(rhs) {}
int ArrayLookup::evaluate() {
    PRINTDEBUG("(ArrayLookup)")
    std::cout << "(ArrayLookup) exit XXXXXXXXXXX" << std::endl;
    exit(1);
    return -1;
}

ArrayLength::ArrayLength(Exp *e): e(e) {}
int ArrayLength::evaluate() {
    PRINTDEBUG("(ArrayLength)")
    std::cout << "(ArrLength) exit XXXXXXXXXXX" << std::endl;
    exit(1);
    return -1;
}

Call::Call(Exp *e, Identifier *i, std::list<Exp *> *el): e(e), i(i), el(el) {}
int Call::evaluate() {
    PRINTDEBUG("(Call)")
    ClassDeclSimple *cl = classTable["Factorial"];
    cl->evaluate();
    //std::cout << "(Call): exit" << e->evaluate() << i->evaluate() << std::endl;
    return -1;
}

IntegerLiteral::IntegerLiteral(int i): num(i) {}
int IntegerLiteral::evaluate() {
    PRINTDEBUG("IntegerLiteral)")
    return num;
}

int True::evaluate() {
    PRINTDEBUG("(True)")
    return 1;
}

int False::evaluate() {
    PRINTDEBUG("(False)")
    return 0;
}

int This::evaluate() {
    PRINTDEBUG("(This)")
    std::cout << "(This) exiting XXXXXXXXXXXx" << std::endl;
    exit(1);
    return -1;
}

IdentifierExp::IdentifierExp(std::string str): id(str) {}
int IdentifierExp::evaluate() {
    PRINTDEBUG("(IdentifierExp)")
    std::cout << "(IdentifierExp):" << id << varTable[id] << std::endl;
    return varTable[id];
}

NewArray::NewArray(Exp *e): e(e) {}
int NewArray::evaluate() {
    PRINTDEBUG("(NewArray)")
    std::cout << "(NewArray)XXXXXXXx" << std::endl;
    exit(1);
    return -1;
}

NewObject::NewObject(Identifier *i): i(i) {}
int NewObject::evaluate() {
    PRINTDEBUG("(NewObject)")
    std::cout << "(NewObject): exiting " << i->evaluate() << std::endl;
    exit(1);
    return -1;
}

Not::Not(Exp *e): e(e) {}
int Not::evaluate() {
    PRINTDEBUG("(Not)")
    int result = e->evaluate();
    return !result;
}

NegativeExp::NegativeExp(Exp *e): e(e) {}
int NegativeExp::evaluate() {
    PRINTDEBUG("(NegativeExp)")
    int result = e->evaluate();
    return -result;
}

PositiveExp::PositiveExp(Exp *e): e(e) {}
int PositiveExp::evaluate() {
    PRINTDEBUG("(PositiveExp)")
    int result = e->evaluate();
    return +result;
}

/*******************    STATEMENT CLASS    ****************************/
Block::Block(std::list<Statement *> *sl): sl(sl) {}
void Block::evaluate() {
    //evaluate Block
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->evaluate();
        std::cout << "(Statement)" << std::endl;
    }
    PRINTDEBUG("(Block Bitches)")
}

If::If(Exp *e, Statement *s1, Statement *s2): e(e), s1(s1), s2(s2) {}
void If::evaluate() {
    PRINTDEBUG("(If)")
    int result = e->evaluate();

    if(result) {
        s1->evaluate();
    } else {
        s2->evaluate();
    }
}

While::While(Exp *e, Statement *s): e(e), s(s) {} 
void While::evaluate() {
    int result = e->evaluate();

    while(result) {
        s->evaluate();
    }
    PRINTDEBUG("(While)")
}

Print::Print(Exp *e): e(e) {}
void Print::evaluate() {
    int num = e->evaluate();
    PRINTDEBUG("(Print)")
    std::cout << num;
}

Println::Println(Exp *e): e(e) {}
void Println::evaluate() {
    int num = e->evaluate();
    PRINTDEBUG("(Println)");
    std::cout << num << std::endl;
}

PrintString::PrintString(std::string str): str(str) {}
void PrintString::evaluate() {
    PRINTDEBUG("(PrintString)")
    std::string s(str);
    std::cout << str;
}

PrintStringln::PrintStringln(const std::string str): str(str) {}
void PrintStringln::evaluate() {
    PRINTDEBUG("(PrintStringln)")
    std::cout << str << std::endl;
}

Assign::Assign(Identifier *i, Exp *e): i(i), e(e) {}
void Assign::evaluate() {
    int value = e->evaluate();
    std::string id = i->evaluate();
    PRINTDEBUG("(Assign)")
    std::cout << id << "=" << value << std::endl;

    varTable[id] = value;
}
ArrayAssign::ArrayAssign(Identifier *i, Exp *e1, Exp *e2): i(i), e1(e1), e2(e2) {}
void ArrayAssign::evaluate() {
    PRINTDEBUG("(ArrayAssign)")
    std::cout << "(ArrayAssign) XXXXXXXXX" << std::endl;
}

/*******************    TYPE CLASS    ****************************/
void IntArrayType::evaluate() {
    PRINTDEBUG("(IntArrayType)")
}

void BooleanType::evaluate() {
    PRINTDEBUG("(BooleanType)")
}

void IntegerType::evaluate() {
    PRINTDEBUG("(IntegerType)")
}

IdentifierType::IdentifierType(const std::string s): str(s) {}
void IdentifierType::evaluate() {
    PRINTDEBUG("(IdentifierType)")
}

/*******************    VAR CLASS    ****************************/
VarDecl::VarDecl(Type *t, Identifier *i): t(t), i(i) {}
void VarDecl::evaluate() {
    PRINTDEBUG("(VarDecl)")
    t->evaluate();
    varTable[i->evaluate()];
}

/*******************    FORMAL CLASS    ****************************/
Formal::Formal(Type *t, Identifier *i): t(t), i(i) {}
void Formal::evaluate() {
    PRINTDEBUG("(Formal)")
}

/*******************    METHOD CLASS    ****************************/
MethodDecl::MethodDecl(Type *t, Identifier *i, std::list<Formal *> *fl,std::list<VarDecl *> *vl, std::list<Statement *> *sl, Exp *e): 
t(t), i(i), fl(fl), vl(vl), sl(sl), e(e) {}
void MethodDecl::evaluate() {
    PRINTDEBUG("(MethodDecl)")
    std::cout << "(MethodDecl)----->" << i->evaluate() << std::endl;
    
    //evaluate Formal Declarations
    std::list<Formal *>::iterator formalIter;
    std::cout << "^btfn (formal Start)" << std::endl;
    for(formalIter = fl->begin(); formalIter != fl->end(); formalIter++){
        std::cout << "^agg (formal Start)" << std::endl;
        (*formalIter)->evaluate();
    std::cout << "^csces (formal Start)" << std::endl;
    }

    //evaluate Variable Declarations
    std::list<VarDecl *>::iterator varIter;
    std::cout << "^btfn (var Start)" << std::endl;
    for(varIter = vl->begin(); varIter != vl->end(); varIter++){
        std::cout << "^agg (var Start)" << std::endl;
        (*varIter)->evaluate();
    std::cout << "^csces (var Start)" << std::endl;
    }

    //evaluate Statement Declarations
    std::list<Statement *>::iterator stmtIter;
    std::cout << "^btfn (stmt Start)" << std::endl;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        std::cout << "^agg (stmt Start)" << std::endl;
        (*stmtIter)->evaluate();
    std::cout << "^csces (stmt Start)" << std::endl;
    }

    //evaluate Expression
    std::cout << "firing last expr statement\n";
    int result = e->evaluate();
}

/******************    CLASS DECLARATION SUB-CLASS    ************/
ClassDeclSimple::ClassDeclSimple(Identifier *i, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml): i(i), vl(vl), ml(ml) {}
void ClassDeclSimple::evaluate() {
    PRINTDEBUG("(ClassDeclSimple)")
    std::cout << "(ClassDeclSimple)----->" << i->evaluate() << std::endl;    
    classTable[i->evaluate()] = this;

    //evaluate Variable Declarations
    std::list<VarDecl *>::iterator varDeclIter;
    std::cout << "^btfn (Var Start)" << std::endl;
    for(varDeclIter = vl->begin(); varDeclIter != vl->end(); varDeclIter++){
        std::cout << "^agg (Var Start)" << std::endl;
        (*varDeclIter)->evaluate();
    std::cout << "^csces (Var Start)" << std::endl;
    }

    //evaluate Method Declarations
    std::list<MethodDecl *>::iterator methodDeclIter;
    std::cout << "^btfn (method Start)" << std::endl;
    for(methodDeclIter = ml->begin(); methodDeclIter != ml->end(); methodDeclIter++){
        std::cout << "^agg (meth Start)" << std::endl;
        (*methodDeclIter)->evaluate();
    std::cout << "^csces (method Start)" << std::endl;
    }

}

ClassDeclExtends::ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml): i(i), j(j), vl(vl), ml(ml) {}
void ClassDeclExtends::evaluate() {
    PRINTDEBUG("(ClassDeclExtends)")
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
    
    PRINTDEBUG("(MainClass)")
};

/*******************    PROGRAM CLASS ****************************/
Program::Program(MainClass *m, std::list<ClassDecl *> *cl): m(m), cl(cl) {}
void Program::evaluate() {
    PRINTDEBUG("\n^ (Program Start)...\n")
    
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
    
    PRINTDEBUG("\n...(Program End) $")
};

std::map<std::string, int> varTable;
std::map<std::string, ClassDeclSimple *> classTable;
