#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include "node.h"
#define PRINTDEBUG(x) //std::cout << x; // comment out print statement to remove the printing

bool type_error = false;

/*******************    IDENTIFIER CLASS    *********************/
Identifier::Identifier(const std::string str): id(str) {}
std::string Identifier::visit() {
    //std::cout << "Identifier:" << id << std::endl;
    return id;
}

/*******************    EXP SUB-CLASSES    ****************************/
And::And(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno)  {}
Types And::visit() {
    PRINTDEBUG("(And)");
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Boolean || right != Boolean) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '&&'" << std::endl;
        type_error = true;
    }
    return Boolean;
}

Or::Or(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types Or::visit() {
    PRINTDEBUG("(Or)");
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Boolean || right != Boolean) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '||'" << std::endl;
        type_error = true;
    }
    return Boolean;
}

Is::Is(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types Is::visit() {
    PRINTDEBUG("(Is)");
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != right) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '=='" << std::endl;
        type_error = true;
    }
    return Boolean;
}

IsNot::IsNot(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types IsNot::visit() {
    PRINTDEBUG("(IsNot)")
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != right) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '!='" << std::endl;
        type_error = true;
    }
    return Boolean;
}

LessThan::LessThan(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types LessThan::visit() {
    PRINTDEBUG("(LessThan)")
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '<'" << std::endl;
        type_error = true;
    }
    return Boolean;
}

LessThanEqual::LessThanEqual(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types LessThanEqual::visit() {
    PRINTDEBUG("LessThanEqual)")
    Types left = lhs->visit();
    Types right = rhs->visit();

    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '<='" << std::endl;
        type_error = true;
    }
    return Boolean;
}

GreaterThan::GreaterThan(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types GreaterThan::visit() {
    PRINTDEBUG("(GreaterThan)")
    Types left = lhs->visit();
    Types right = rhs->visit();

    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '>'" << std::endl;
        type_error = true;
    }
    return Boolean;
}

GreaterThanEqual::GreaterThanEqual(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types GreaterThanEqual::visit() {
    PRINTDEBUG("(GreaterThanEqual)")
    Types left = lhs->visit();
    Types right = rhs->visit();

    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '>='" << std::endl;
        type_error = true;
    }
    return Boolean;
}

Plus::Plus(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types Plus::visit() {
    PRINTDEBUG("(Plus)")
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '+'" << std::endl;
        type_error = true;
    }
    return Integer;

}

Minus::Minus(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types Minus::visit() {
    PRINTDEBUG("(Minus)")
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '-'" << std::endl;
        type_error = true;
    }
    return Integer;

}

Times::Times(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types Times::visit() {
    PRINTDEBUG("(Times)")
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '*'" << std::endl;
        type_error = true;
    }
    return Integer;
}

Div::Div(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types Div::visit() {
    PRINTDEBUG("(Div)")
    Types left = lhs->visit();
    Types right = rhs->visit();
    
    if(left != Integer || right != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '/'" << std::endl;
        type_error = true;
    }
    return Integer;
}

ArrayLookup::ArrayLookup(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
Types ArrayLookup::visit() {
    PRINTDEBUG("(ArrayLookup) NEEDS TO BE IMPLEMENTED")
    //std::cout << "(ArrayLookup) exit XXXXXXXXXXX" << std::endl;
    //exit(1);
    return Integer;
}

ArrayLength::ArrayLength(Exp *e): e(e) {}
Types ArrayLength::visit() {
    PRINTDEBUG("(ArrayLength)")
    //std::cout << "(ArrLength) exit XXXXXXXXXXX" << std::endl;
    //exit(1);
    return Integer;
}

Call::Call(Exp *e, Identifier *i, std::list<Exp *> *el): e(e), i(i), el(el) {}
Types Call::visit() {
    PRINTDEBUG("(Call)")
    ClassDeclSimple *cl = classTable["Factorial"];
    cl->visit();
    //std::cout << "(Call): exit" << e->visit() << i->visit() << std::endl;
    std::cout << "(Call)MODIFY THIS TO RETURN DYNAMIC RETURN TYPES" << std::endl;
    
    return Integer;
}

IntegerLiteral::IntegerLiteral(int i): num(i) {}
Types IntegerLiteral::visit() {
    PRINTDEBUG("IntegerLiteral)")
    return Integer;
}

Types True::visit() {
    PRINTDEBUG("(True)")
    return Boolean;
}

Types False::visit() {
    PRINTDEBUG("(False)")
    return Boolean;
}

Types This::visit() {
    PRINTDEBUG("(This)")
    //std::cout << "(This) exiting XXXXXXXXXXXx" << std::endl;
    //exit(1);
    return Object;
}

IdentifierExp::IdentifierExp(std::string str): id(str) {}
Types IdentifierExp::visit() {
    PRINTDEBUG("(IdentifierExp)")
    std::cout << "(IdentifierExp):MODIFY THIS TO RETURN DYNAMIC TYPE OF VAR IN VAR TABLE" << id << varTable[id] << std::endl;
    return Integer;
}

NewArray::NewArray(Exp *e): e(e) {}
Types NewArray::visit() {
    PRINTDEBUG("(NewArray)")
    //std::cout << "(NewArray)XXXXXXXx" << std::endl;
    //exit(1);
    return Array;
}

NewObject::NewObject(Identifier *i): i(i) {}
Types NewObject::visit() {
    PRINTDEBUG("(NewObject)")
    std::cout << "(NewObject): exiting " << i->visit() << std::endl;
    //exit(1);
    return Object;
}

Not::Not(Exp *e, int lineno): e(e), lineno(lineno) {}
Types Not::visit() {
    PRINTDEBUG("(Not)")
    if(e->visit() != Boolean) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '!'" << std::endl;
        type_error = true;
    }
    return Boolean;
}

NegativeExp::NegativeExp(Exp *e, int lineno): e(e), lineno(lineno) {}
Types NegativeExp::visit() {
    PRINTDEBUG("(NegativeExp)")
    if(e->visit() != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '-'" << std::endl;
        type_error = true;
    }
    return Integer;
}

PositiveExp::PositiveExp(Exp *e, int lineno): e(e), lineno(lineno) {}
Types PositiveExp::visit() {
    PRINTDEBUG("(PositiveExp)")
    if(e->visit() != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '+'" << std::endl;
        type_error = true;
    }
    return Integer;
}

/*******************    STATEMENT CLASS    ****************************/
Block::Block(std::list<Statement *> *sl): sl(sl) {}
void Block::visit() {
    //evaluate Block
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->visit();
        std::cout << "(Statement)" << std::endl;
    }
    PRINTDEBUG("(Block)")
}

If::If(Exp *e, Statement *s1, Statement *s2, int lineno): e(e), s1(s1), s2(s2), lineno(lineno) {}
void If::visit() {
    PRINTDEBUG("(If)")
    Types result = e->visit();

    if(result != Boolean) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types" << std::endl;
        type_error = true;
    }
}

While::While(Exp *e, Statement *s, int lineno): e(e), s(s), lineno(lineno) {} 
void While::visit() {
    int result = e->visit();
    
    if(result != Boolean) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types" << std::endl;
        type_error = true;
    }
    PRINTDEBUG("(While)")
}

Print::Print(Exp *e, int lineno): e(e), lineno(lineno) {}
void Print::visit() {
    if(e->visit() != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types" << std::endl;
        type_error = true;
    }
    PRINTDEBUG("(Print)")
}

Println::Println(Exp *e, int lineno): e(e), lineno(lineno) {}
void Println::visit() {
    PRINTDEBUG("(Println)");
    if(e->visit() != Integer) {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types" << std::endl;
        type_error = true;
    }
}

PrintString::PrintString(std::string str): str(str) {}
void PrintString::visit() {
    PRINTDEBUG("(PrintString)")
}

PrintStringln::PrintStringln(const std::string str): str(str) {}
void PrintStringln::visit() {
    PRINTDEBUG("(PrintStringln)")
}

Assign::Assign(Identifier *i, Exp *e): i(i), e(e) {}
void Assign::visit() {
    int value = e->visit();
    std::string id = i->visit();
    PRINTDEBUG("(Assign) NEEDS TO CHECK FOR TYPES!!!!!!")
    std::cout << id << "=" << value << std::endl;

    varTable[id] = value;
}
ArrayAssign::ArrayAssign(Identifier *i, Exp *e1, Exp *e2): i(i), e1(e1), e2(e2) {}
void ArrayAssign::visit() {
    PRINTDEBUG("(ArrayAssign)")
    std::cout << "(ArrayAssign) XXXXXXXXX" << std::endl;
}

/*******************    TYPE CLASS    ****************************/
Types IntArrayType::getType() {
    PRINTDEBUG("(IntArrayType)")
    return Array;
}

Types BooleanType::getType() {
    PRINTDEBUG("(BooleanType)")
    return Boolean;
}

Types IntegerType::getType() {
    PRINTDEBUG("(IntegerType)")
    return Integer;
}

IdentifierType::IdentifierType(const std::string s): str(s) {}
Types IdentifierType::getType() {
    PRINTDEBUG("(IdentifierType)")
    return Object;
}

/*******************    VAR CLASS    ****************************/
VarDecl::VarDecl(Type *t, Identifier *i): t(t), i(i) {}
void VarDecl::visit() {
    PRINTDEBUG("(VarDecl)")
    t->getType();
    varTable[i->visit()];
}

/*******************    FORMAL CLASS    ****************************/
Formal::Formal(Type *t, Identifier *i): t(t), i(i) {}
void Formal::visit() {
    PRINTDEBUG("(Formal)")
}

/*******************    METHOD CLASS    ****************************/
MethodDecl::MethodDecl(Type *t, Identifier *i, std::list<Formal *> *fl,std::list<VarDecl *> *vl, std::list<Statement *> *sl, Exp *e): 
t(t), i(i), fl(fl), vl(vl), sl(sl), e(e) {}
void MethodDecl::visit() {
    PRINTDEBUG("(MethodDecl)")
    std::cout << "(MethodDecl)----->" << i->visit() << std::endl;
    
    //evaluate Formal Declarations
    std::list<Formal *>::iterator formalIter;
    std::cout << "^btfn (formal Start)" << std::endl;
    for(formalIter = fl->begin(); formalIter != fl->end(); formalIter++){
        std::cout << "^agg (formal Start)" << std::endl;
        (*formalIter)->visit();
    std::cout << "^csces (formal Start)" << std::endl;
    }

    //evaluate Variable Declarations
    std::list<VarDecl *>::iterator varIter;
    std::cout << "^btfn (var Start)" << std::endl;
    for(varIter = vl->begin(); varIter != vl->end(); varIter++){
        std::cout << "^agg (var Start)" << std::endl;
        (*varIter)->visit();
    std::cout << "^csces (var Start)" << std::endl;
    }

    //evaluate Statement Declarations
    std::list<Statement *>::iterator stmtIter;
    std::cout << "^btfn (stmt Start)" << std::endl;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        std::cout << "^agg (stmt Start)" << std::endl;
        (*stmtIter)->visit();
    std::cout << "^csces (stmt Start)" << std::endl;
    }

    //evaluate Expression
    std::cout << "firing last expr statement\n";
    int result = e->visit();
}

/******************    CLASS DECLARATION SUB-CLASS    ************/
ClassDeclSimple::ClassDeclSimple(Identifier *i, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml): i(i), vl(vl), ml(ml) {}
void ClassDeclSimple::visit() {
    PRINTDEBUG("(ClassDeclSimple)")
    std::cout << "(ClassDeclSimple)----->" << i->visit() << std::endl;    
    classTable[i->visit()] = this;

    //evaluate Variable Declarations
    std::list<VarDecl *>::iterator varDeclIter;
    for(varDeclIter = vl->begin(); varDeclIter != vl->end(); varDeclIter++){
        (*varDeclIter)->visit();
    }

    //evaluate Method Declarations
    std::list<MethodDecl *>::iterator methodDeclIter;
    for(methodDeclIter = ml->begin(); methodDeclIter != ml->end(); methodDeclIter++){
        (*methodDeclIter)->visit();
    }

}

ClassDeclExtends::ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml): i(i), j(j), vl(vl), ml(ml) {}
void ClassDeclExtends::visit() {
    PRINTDEBUG("(ClassDeclExtends)")
    std::cout << "(ClassDeclExtends)" << std::endl;
}

/*******************    MAIN CLASS    ****************************/
MainClass::MainClass(Identifier *i1, Identifier *i2, Statement *s): i1(i1), i2(i2), s(s) {}
void MainClass::visit() {
    //evaluate Identifiers
    i1->visit();
    i2->visit();

    //evaluate Statement
    s->visit();
    
    PRINTDEBUG("(MainClass)")
};

/*******************    PROGRAM CLASS ****************************/
Program::Program(MainClass *m, std::list<ClassDecl *> *cl): m(m), cl(cl) {}
void Program::visit() {
    PRINTDEBUG("\n^ (Program Start)...\n")
    
    //evaluate ClassDeclarations
    std::list<ClassDecl *>::iterator classDeclIter;
    for(classDeclIter = cl->begin(); classDeclIter != cl->end(); classDeclIter++){
        (*classDeclIter)->visit();
    }

    //evaluate MainClass    
    m->visit();
    
    //type errors exist in the program
    if(type_error) {
        exit(1);
    }
    PRINTDEBUG("\n...(Program End Type Check Completed Gracefully) $")
};

std::map<std::string, int> varTable;
std::map<std::string, ClassDeclSimple *> classTable;
