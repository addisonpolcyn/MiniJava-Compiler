#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include "node.h"
#define PRINTDEBUG(x) std::cout << x << std::endl; // comment out print statement to remove the printing

bool type_error = false;    //boolean value true denotes type_error present in Tree, false Tree syntax is type valid
std::string mainClassName;  //string name of the main class 

std::map<std::string, ClassDecl *> classTable;      //map of classes in program
std::map<std::string, VarDecl *> type_class_scope;  //map of fields in current class scope
std::map<std::string, VarDecl *> type_local_scope;  //map of variables in current scope inlcuding current class variables and method variables

/*******************    IDENTIFIER CLASS    *********************/
Identifier::Identifier(const std::string str): id(str) {}
std::string Identifier::toString() {
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
    //ClassDeclSimple *cl = classTable["Factorial"];
    //cl->visit();
    std::cout << "(Call)MODIFY THIS TO RETURN DYNAMIC RETURN TYPES" << std::endl;
    
    return Integer;
}

IntegerLiteral::IntegerLiteral(int i): num(i) {}
Types IntegerLiteral::visit() {
    PRINTDEBUG("(IntegerLiteral)")
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
    return type_local_scope[id]->t->getType();
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

Assign::Assign(Identifier *i, Exp *e, int lineno): i(i), e(e), lineno(lineno) {}
void Assign::visit() {
    PRINTDEBUG("(Assign)")
    
    VarDecl *var = type_local_scope[i->toString()];
    if(var->t->getType() != e->visit()) {
        std::cerr << "Type Violation in Line " << lineno << " : invalid assignment type" << std::endl;
        type_error = true;
    }
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
}

/*******************    FORMAL CLASS    ****************************/
Formal::Formal(Type *t, Identifier *i): t(t), i(i) {}
void Formal::visit() {
    PRINTDEBUG("(Formal)")
}

/*******************    METHOD CLASS    ****************************/
MethodDecl::MethodDecl(Type *t, Identifier *i, std::list<Formal *> *fl,std::list<VarDecl *> *vl, std::list<Statement *> *sl, Exp *e, int lineno): 
t(t), i(i), fl(fl), vl(vl), sl(sl), e(e), lineno(lineno) {}
void MethodDecl::visit() {
    PRINTDEBUG("(MethodDecl)")
    
    //init method scope
    type_local_scope.clear();

    //iterate class scope into method scope
    std::map<std::string, VarDecl *>::iterator it;
    for (it = type_class_scope.begin(); it != type_class_scope.end(); it++) {
        type_local_scope[it->first] = it->second;
    }
    
    //evaluate Formal Declarations
    std::list<Formal *>::iterator formalIter;
    for(formalIter = fl->begin(); formalIter != fl->end(); formalIter++){
        std::string paramName = (*formalIter)->i->toString();
        
        //type check parameter 
        if(parameters.count(paramName)){
            std::cerr << "Type Violation in Line " << lineno << " : error: duplicate parameter: " << paramName << std::endl;
            type_error = true;
        } else {
            parameters[paramName] = *formalIter;
            type_local_scope[paramName] = new VarDecl((*formalIter)->t, (*formalIter)->i);
            (*formalIter)->visit();

        }
    }

    //evaluate Variable Declarations
    std::list<VarDecl *>::iterator varIter;
    for(varIter = vl->begin(); varIter != vl->end(); varIter++){
        std::string varName = (*varIter)->i->toString();

        //type check locals
        if(localVariables.count(varName)){
            std::cerr << "Type Violation in Line " << lineno << " : error: duplicate local variable: " << varName << std::endl;
            type_error = true;
        } else {
            localVariables[varName] = *varIter;
            type_local_scope[varName] = *varIter;
            (*varIter)->visit();
        }
    }
    
    //evaluate Statement Declarations
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->visit();
    }

    //evaluate return Expression
    if(t->getType() != e->visit()) {
        std::cerr << "Type Violation in Line " << lineno << " : error: incompatible return types" << std::endl;
        type_error = true;
    }
}

/******************    CLASS DECLARATION SUB-CLASS    ************/
ClassDeclSimple::ClassDeclSimple(Identifier *i, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml, int lineno): i(i), vl(vl), ml(ml), lineno(lineno) {}
void ClassDeclSimple::visit() {
    PRINTDEBUG("(ClassDeclSimple)")

    //init class scope
    type_class_scope.clear();

    //evaluate Variable Declarations
    std::list<VarDecl *>::iterator varDeclIter;
    for(varDeclIter = vl->begin(); varDeclIter != vl->end(); varDeclIter++){
        std::string fieldName = (*varDeclIter)->i->toString();
        
        //type check variable
        if(fieldVariables.count(fieldName)){
            std::cerr << "Type Violation in Line " << lineno << " : error: duplicate field: " << fieldName << std::endl;
            type_error = true;
        } else {
            fieldVariables[fieldName] = *varDeclIter;
            type_class_scope[fieldName] = *varDeclIter;
            (*varDeclIter)->visit();
        }

    }

    //evaluate Method Declarations
    std::list<MethodDecl *>::iterator methodDeclIter;
    for(methodDeclIter = ml->begin(); methodDeclIter != ml->end(); methodDeclIter++){
        std::string methodName = (*methodDeclIter)->i->toString();

        //type check method
        if(methods.count(methodName)){
            std::cerr << "Type Violation in Line " << lineno << " : error: duplicate method: " << methodName << std::endl;
            type_error = true;
        } else {
            methods[methodName] = *methodDeclIter;
            (*methodDeclIter)->visit();
        }

    }

}
std::string ClassDeclSimple::getName() {
    return i->toString();
}

ClassDeclExtends::ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml, int lineno): i(i), j(j), vl(vl), ml(ml), lineno(lineno) {}
void ClassDeclExtends::visit() {
    PRINTDEBUG("(ClassDeclExtends)")
    std::cout << "(ClassDeclExtends)" << std::endl;
}
std::string ClassDeclExtends::getName() {
    return i->toString();
}


/*******************    MAIN CLASS    ****************************/
MainClass::MainClass(Identifier *i1, Identifier *i2, Statement *s): i1(i1), i2(i2), s(s) {}
void MainClass::visit() {
    //evaluate Identifiers
    i1->toString();
    i2->toString();

    //evaluate Statement
    s->visit();
    
    PRINTDEBUG("(MainClass)")
};

/*******************    PROGRAM CLASS ****************************/
Program::Program(MainClass *m, std::list<ClassDecl *> *cl, int lineno): m(m), cl(cl), lineno(lineno) {}
void Program::visit() {
    PRINTDEBUG("\n^ (Program Start)...\n")
    
    //load main class name into global variable
    mainClassName = m->i1->toString();

    //evaluate ClassDeclarations
    std::list<ClassDecl *>::iterator classDeclIter;
    for(classDeclIter = cl->begin(); classDeclIter != cl->end(); classDeclIter++){
        std::string className = (*classDeclIter)->getName();

        //type check class
        if(classTable.count(className) || className.compare(mainClassName) == 0){
            std::cerr << "Type Violation in Line " << lineno << " : error: duplicate class: " << className << std::endl;
            type_error = true;
        } else {
            classTable[className] = (*classDeclIter);
            (*classDeclIter)->visit();
        }
    }

    //evaluate MainClass    
    m->visit();
    
    //type errors exist in the program
    if(type_error) {
        exit(1);
    }
    PRINTDEBUG("\n...(Program End Type Check Completed Gracefully) $")
};

