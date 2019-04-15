#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector> 

#include "node.h"
#define PRINTDEBUG(x) //std::cout << x << std::endl; // comment out print statement to remove the printing

bool type_error = false;    //boolean value true denotes type_error present in Tree, false Tree syntax is type valid
std::string mainClassName;  //string name of the main class 

ClassDecl *currentClass;
std::map<std::string, ClassDecl *> classTable;      //map of classes in program
std::map<std::string, VarDecl *> type_class_scope;  //map of fields in current class scope
std::map<std::string, VarDecl *> type_local_scope;  //map of variables in current scope inlcuding current class variables and method variables
std::map<std::string, std::string> scope_type;
std::map<std::string, int> scope;

std::string buffer;
std::vector<std::string> text;
std::string current_reg("r0");    //current temp storage register ex. "r1"

/*******************    IDENTIFIER CLASS    *********************/
Identifier::Identifier(const std::string str): id(str) {}
std::string Identifier::toString() {
    return id;
}

/*******************    EXP SUB-CLASSES    ****************************/
And::And(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno)  {}
std::string And::visit() {
    PRINTDEBUG("(And)");
    std::string left = lhs->visit();
    std::string right = rhs->visit();    
    if(left != "boolean" || right != "boolean") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '&&'" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void And::evaluate() {
    lhs->evaluate();
    current_reg = "r1";
    rhs->evaluate();
    current_reg = "r0";
    buffer += "    and r0, r0, r1\n"; //add values from r0 and r1, store in r0
}

Or::Or(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string Or::visit() {
    PRINTDEBUG("(Or)");
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "boolean" || right != "boolean") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '||'" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void Or::evaluate() {
    lhs->evaluate();
    current_reg = "r1";
    rhs->evaluate();
    current_reg = "r0";
    buffer += "    orr r0, r0, r1\n"; //add values from r0 and r1, store in r0
}

Is::Is(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string Is::visit() {
    PRINTDEBUG("(Is)");
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != right) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '=='" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void Is::evaluate() {
    //evaluate expr
    lhs->evaluate();
    current_reg = "r1";
    rhs->evaluate();
    current_reg = "r0";

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    beq 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";
}

IsNot::IsNot(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string IsNot::visit() {
    PRINTDEBUG("(IsNot)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != right) {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '!='" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void IsNot::evaluate() {
    int result = 0;
   // if(*(int *)lhs->evaluate() != *(int *)rhs->evaluate()){
     //   result = 1;
    //}
    void *ptr = &result;
     
}

LessThan::LessThan(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string LessThan::visit() {
    PRINTDEBUG("(LessThan)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '<'" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void LessThan::evaluate() {
    int result = 0;
    //if(*(int *)lhs->evaluate() < *(int *)rhs->evaluate()){
      //  result = 1;
    //}
    void *ptr = &result;
     
}

LessThanEqual::LessThanEqual(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string LessThanEqual::visit() {
    PRINTDEBUG("LessThanEqual)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '<='" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void LessThanEqual::evaluate() {
    int result = 0;
   // if(*(int *)lhs->evaluate() <= *(int *)rhs->evaluate()){
     //   result = 1;
    //}
    void *ptr = &result;
     
}

GreaterThan::GreaterThan(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string GreaterThan::visit() {
    PRINTDEBUG("(GreaterThan)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '>'" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void GreaterThan::evaluate() {
    int result = 0;
    //if(*(int *)lhs->evaluate() > *(int *)rhs->evaluate()){
      //  result = 1;
    //}
    void *ptr = &result;
     
}

GreaterThanEqual::GreaterThanEqual(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string GreaterThanEqual::visit() {
    PRINTDEBUG("(GreaterThanEqual)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '>='" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void GreaterThanEqual::evaluate() {
    int result = 0;
    //if(*(int *)lhs->evaluate() >= *(int *)rhs->evaluate()){
      //  result = 1;
    //}
    void *ptr = &result;
     
}

Plus::Plus(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string Plus::visit() {
    PRINTDEBUG("(Plus)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '+'" << std::endl;
        type_error = true;
    }
    return "int";

}
void Plus::evaluate() {
    lhs->evaluate();
    current_reg = "r1";
    rhs->evaluate();
    current_reg = "r0";
    buffer += "    add r0, r0, r1\n"; //add values from r0 and r1, store in r0
}

Minus::Minus(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string Minus::visit() {
    PRINTDEBUG("(Minus)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '-'" << std::endl;
        type_error = true;
    }
    return "int";

}
void Minus::evaluate() {
    lhs->evaluate();
    current_reg = "r1";
    rhs->evaluate();
    current_reg = "r0";
    buffer += "    sub r0, r0, r1\n"; //add values from r0 and r1, store in r0
}

Times::Times(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string Times::visit() {
    PRINTDEBUG("(Times)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '*'" << std::endl;
        type_error = true;
    }
    return "int";
}
void Times::evaluate() {
    lhs->evaluate();
    current_reg = "r1";
    rhs->evaluate();
    current_reg = "r0";
    buffer += "    mul r0, r0, r1\n"; //add values from r0 and r1, store in r0
}

Div::Div(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string Div::visit() {
    PRINTDEBUG("(Div)")
    std::string left = lhs->visit();
    std::string right = rhs->visit();
    if(left != "int" || right != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types for binary operator '/'" << std::endl;
        type_error = true;
    }
    return "int";
}
void Div::evaluate() {
    //int result = *(int *)lhs->evaluate() / *(int *)rhs->evaluate();
    //void *ptr = &result;
     //
}

ArrayLookup::ArrayLookup(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string ArrayLookup::visit() {
    PRINTDEBUG("(ArrayLookup)")
    return "int";
}
void ArrayLookup::evaluate() {
    PRINTDEBUG("BROKEN EXPR EVAL")
    int val = 1;
    void *ptr = &val;
     
}

ArrayLength::ArrayLength(Exp *e): e(e) {}
std::string ArrayLength::visit() {
    PRINTDEBUG("(ArrayLength)")
    return "int";
}
void ArrayLength::evaluate() {
    PRINTDEBUG("BROKEN EXPR EVAL")
    int val = 1;
    void *ptr = &val;
     
}

Call::Call(Exp *e, Identifier *i, std::list<Exp *> *el, int lineno): e(e), i(i), el(el), lineno(lineno) {}
std::string Call::visit() {
    PRINTDEBUG("(Call)")
    std::string objectType = e->visit();
    
    //check if class object type exists
    if(!classTable.count(objectType)){
        std::cerr << "Type Violation in Line " << lineno << " : error cannot find class:" << objectType << std::endl;
        type_error = true;
        return "int";
    }
    ClassDecl *cl = classTable[objectType];
    std::string methodName = i->toString();
    std::map<std::string, MethodDecl *> methods = cl->methods;
    
    //check if method exists
    if(!methods.count(methodName)){
        std::cerr << "Type Violation in Line " << lineno << " : error method:" << methodName << " does not belong to class:" << objectType << std::endl;
        type_error = true;
        return "int";
    }
    MethodDecl *method = methods[methodName];
    std::list<Formal *> *fl = method->fl;
    std::string returnType = method->t->getType();

    //check if arguments size matches parameters size
    int defSize = fl->size();
    int argSize = el->size();
    if(defSize != argSize) {
        std::cerr << "Type Violation in Line " << lineno << " : error expected:" << defSize << " argument(s) but recieved:" << argSize << std::endl;
        type_error = true;
        return returnType;
    }
    
    //check if parameters are valid
    std::list<Formal *>::iterator formalIter;
    std::list<Exp *>::iterator expIter = el->begin();
    for(formalIter = fl->begin(); formalIter != fl->end(); formalIter++){
        std::string param_Type = (*formalIter)->t->getType();
        std::string expr_Type = (*expIter)->visit();
        
        //type check parameter 
        if(param_Type != expr_Type) {
            std::cerr << "Type Violation in Line " << lineno << " : error invalid arg types for method:" << methodName << std::endl;
            type_error = true;
            return returnType;
        }
        expIter++;
    }

    //iterate over exper list for shits
    return returnType;
}
void Call::evaluate() {
    //get object class and method pointers
    /*
    ClassDecl *cl = (ClassDecl *)e->evaluate();
    std::string methodName = i->toString();
    MethodDecl *method = cl->methods[methodName];
    
    //init scope
 //   scope.clear();
  //  scope_type.clear();

    //load class formal variables keys
    for (auto const& x : cl->fieldVariables) {
        scope[x.first];
        scope_type[x.first] = x.second->t->getType();
    }
    //load method local variable keys
    for (auto const& x : method->localVariables) {
        scope[x.first];
        scope_type[x.first] = x.second->t->getType();
    }

    //load and input argument parameter values
    std::list<Formal *> *fl = method->fl;
    std::list<Formal *>::iterator formalIter;
    std::list<Exp *>::iterator expIter = el->begin();
    for(formalIter = fl->begin(); formalIter != fl->end(); formalIter++){
        std::string key = (*formalIter)->i->toString();
        std::string expr_Type = (*expIter)->visit();
        void * expr_value = (*expIter)->evaluate();
        int val = *(int *)(*expIter)->evaluate();
        scope[key] = val;
        scope_type[key] = expr_Type;
        expIter++;
    }
    return method->evaluate();*/
}

IntegerLiteral::IntegerLiteral(int i): num(i) {}
std::string IntegerLiteral::visit() {
    PRINTDEBUG("(IntegerLiteral)")
    return "int";
}
void IntegerLiteral::evaluate() {
    int val = num;
    void *ptr = &val;
    buffer += "    ldr "+current_reg+", ="+std::to_string(num)+"\n";  //load value into r0    
}

std::string True::visit() {
    PRINTDEBUG("(True)")
    return "boolean";
}
void True::evaluate() {
    int val = 1;
    void *ptr = &val;
    buffer += "    ldr "+current_reg+", =1\n";  //load value into r0    
}

std::string False::visit() {
    PRINTDEBUG("(False)")
    return "boolean";
}
void False::evaluate() {
    int val = 0;
    void *ptr = &val;
    buffer += "    ldr "+current_reg+", =0\n";  //load value into r0    
}


std::string This::visit() {
    return currentClass->getName();
}
void This::evaluate() {
    ClassDecl *cl = currentClass;
    void *ptr = &(*cl);
}

IdentifierExp::IdentifierExp(std::string str): id(str) {}
std::string IdentifierExp::visit() {
    PRINTDEBUG("(IdentifierExp)")
    return type_local_scope[id]->t->getType();
}
void IdentifierExp::evaluate() {
    PRINTDEBUG("(IdentifierExp)")
    int val = scope[id];
    void * ptr = &val;
}

NewArray::NewArray(Exp *e): e(e) {}
std::string NewArray::visit() {
    PRINTDEBUG("(NewArray)")
    return "int []";
}
void NewArray::evaluate() {
    PRINTDEBUG("BROKEN EXPR EVAL")
    int val = 1;
    void *ptr = &val;
}

NewObject::NewObject(Identifier *i): i(i) {}
std::string NewObject::visit() {
    PRINTDEBUG("(NewObject)")
    return i->toString();
}
void NewObject::evaluate() {
    ClassDecl *cl = classTable[i->toString()];
    void *ptr = &(*cl);
}

Not::Not(Exp *e, int lineno): e(e), lineno(lineno) {}
std::string Not::visit() {
    PRINTDEBUG("(Not)")
    if(e->visit() != "boolean") {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '!'" << std::endl;
        type_error = true;
    }
    return "boolean";
}
void Not::evaluate() {
    int val = 0;
//    if(*(int *)e->evaluate() == 0) {
  //      val = 1;
    //}
    void *ptr = &val;
}

NegativeExp::NegativeExp(Exp *e, int lineno): e(e), lineno(lineno) {}
std::string NegativeExp::visit() {
    PRINTDEBUG("(NegativeExp)")
    if(e->visit() != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '-'" << std::endl;
        type_error = true;
    }
    return "int";
}
void NegativeExp::evaluate() {
   // int val = -(*(int *)e->evaluate());
    //void *ptr = &val;
}

PositiveExp::PositiveExp(Exp *e, int lineno): e(e), lineno(lineno) {}
std::string PositiveExp::visit() {
    PRINTDEBUG("(PositiveExp)")
    if(e->visit() != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types for binary operator '+'" << std::endl;
        type_error = true;
    }
    return "int";
}
void PositiveExp::evaluate() {
//    int val = +(*(int *)e->evaluate());
  //  void *ptr = &val;
    // 
}

/*******************    STATEMENT CLASS    ****************************/
Block::Block(std::list<Statement *> *sl): sl(sl) {}
void Block::visit() {
    //evaluate Block
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->visit();
        PRINTDEBUG("(Statement)")
    }
    PRINTDEBUG("(Block)")
}
void Block::evaluate() {
    //evaluate Block
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->evaluate();
        PRINTDEBUG("(Statement)")
    }
    PRINTDEBUG("(Block)")
    buffer += "\n";
}

If::If(Exp *e, Statement *s1, Statement *s2, int lineno): e(e), s1(s1), s2(s2), lineno(lineno) {}
void If::visit() {
    PRINTDEBUG("(If)")
    if(e->visit() != "boolean") {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types" << std::endl;
        type_error = true;
    }
    s1->visit();

    PRINTDEBUG("(Else)")
    s2->visit();

}
void If::evaluate() {
    //evaluate boolean expr
    e->evaluate();

    //compare equality
    buffer += "    cmp r0, #1\n";
    buffer += "    beq 1f\n";
    s2->evaluate();
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    s1->evaluate();            
    
    //branch 2
    buffer += "2:      \n";
}

While::While(Exp *e, Statement *s, int lineno): e(e), s(s), lineno(lineno) {} 
void While::visit() {
    if(e->visit() != "boolean") {
        std::cerr << "Type Violation in Line " << lineno << " : incomparable types" << std::endl;
        type_error = true;
    }
    s->visit();
    PRINTDEBUG("(While)")
}
void While::evaluate() {
//    while(*(int *)e->evaluate()) {
  //      s->evaluate();        
    //}
}

Print::Print(Exp *e, int lineno): e(e), lineno(lineno) {}
void Print::visit() {
    if(e->visit() != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types" << std::endl;
        type_error = true;
    }
    PRINTDEBUG("(Print)")
}
void Print::evaluate() {
    e->evaluate();
    PRINTDEBUG("(Print)")

    buffer += "    mov r1, r0\n";
    buffer += "    ldr r0, =int_print\n";
    buffer += "    bl  printf\n";
}

Println::Println(Exp *e, int lineno): e(e), lineno(lineno) {}
void Println::visit() {
    PRINTDEBUG("(Println)");
    if(e->visit() != "int") {
        std::cerr << "Type Violation in Line " << lineno << " : bad operand types" << std::endl;
        type_error = true;
    }
}
void Println::evaluate() {
    e->evaluate();
    PRINTDEBUG("(Println)")
    
    buffer += "    mov r1, r0\n";
    buffer += "    ldr r0, =int_println\n";
    buffer += "    bl  printf\n";
}

PrintString::PrintString(std::string str): str(str) {}
void PrintString::visit() {
    PRINTDEBUG("(PrintString)")
}
void PrintString::evaluate() {
    PRINTDEBUG("(PrintString)")

    int n = text.size() + 1;
    std::string txt = "string"+std::to_string(n)+": .asciz \""+str+"\"\n";
    buffer += "    ldr r0, =string"+std::to_string(n)+"\n";
    buffer += "    bl  printf\n";
    text.push_back(txt);
}

PrintStringln::PrintStringln(const std::string str): str(str) {}
void PrintStringln::visit() {
    PRINTDEBUG("(PrintStringln)")
}
void PrintStringln::evaluate() {
    PRINTDEBUG("(PrintStringln)")
    int n = text.size() + 1;
    std::string txt = "string"+std::to_string(n)+": .asciz \""+str+"\\n\"\n";
    buffer += "    ldr r0, =string"+std::to_string(n)+"\n";
    buffer += "    bl  printf\n";
    text.push_back(txt);
}

Assign::Assign(Identifier *i, Exp *e, int lineno): i(i), e(e), lineno(lineno) {}
void Assign::visit() {
    PRINTDEBUG("(Assign)")
    
    VarDecl *var = type_local_scope[i->toString()];
    if(var->t->getType() != (e->visit())) {
        std::cerr << "Type Violation in Line " << lineno << " : invalid assignment type" << std::endl;
        type_error = true;
    }
}
void Assign::evaluate() {
    //int val = *(int *)e->evaluate();
    //scope[i->toString()] = val;
}

ArrayAssign::ArrayAssign(Identifier *i, Exp *e1, Exp *e2): i(i), e1(e1), e2(e2) {}
void ArrayAssign::visit() {
    PRINTDEBUG("(ArrayAssign XXXXXXXX)")
}
void ArrayAssign::evaluate() {
    PRINTDEBUG("(Statment Evaluation Broken)")
}

/*******************    TYPE CLASS    ****************************/
std::string IntArrayType::getType() {
    PRINTDEBUG("(IntArrayType)")
    return "int []";
}

std::string BooleanType::getType() {
    PRINTDEBUG("(BooleanType)")
    return "boolean";
}

std::string IntegerType::getType() {
    PRINTDEBUG("(IntegerType)")
    return "int";
}

IdentifierType::IdentifierType(const std::string s): str(s) {}
std::string IdentifierType::getType() {
    PRINTDEBUG("(IdentifierType)")
    return str;
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
    if(t->getType() != (e->visit())) {
        std::cerr << "Type Violation in Line " << lineno << " : error: incompatible return types" << std::endl;
        type_error = true;
    }
}
void MethodDecl::evaluate() {
    //evaluate Statement Declarations
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->evaluate();
    }
    //int returnVal = *(int *)e->evaluate();
    
    //clean scopes
    //scope.clear();
    //scope_type.clear();
    //void * ptr = &returnVal;
     
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
        }

    }
    //iterate over methods
    for (auto const& method : methods) {
        (method.second)->visit();
    }


}
std::string ClassDeclSimple::getName() {
    return i->toString();
}

ClassDeclExtends::ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml, int lineno): i(i), j(j), vl(vl), ml(ml), lineno(lineno) {}
void ClassDeclExtends::visit() {
    PRINTDEBUG("(ClassDeclExtends)")
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
}
void MainClass::evaluate() {
    //evaluate statements
    buffer += ".global main\n";
    buffer += ".balign 4\n";
    buffer += "main:\n";
    buffer += "    push {lr}\n";

    s->evaluate();    
    PRINTDEBUG("(MainClass)")
    
    buffer += "    pop {pc}\n";
}

/*******************    PROGRAM CLASS ****************************/
Program::Program(MainClass *m, std::list<ClassDecl *> *cl, int lineno): m(m), cl(cl), lineno(lineno) {}
void Program::traverse() {
    PRINTDEBUG("\n^ (Program Start)...\n")
    
    //load main class name into global variable
    mainClassName = m->i1->toString();

    //evaluate ClassDeclarations
    std::list<ClassDecl *>::iterator classDeclIter;
    for(classDeclIter = cl->begin(); classDeclIter != cl->end(); classDeclIter++){
        std::string className = (*classDeclIter)->getName();
        
        //type check class
        if(classTable.count(className) || className == mainClassName){
            std::cerr << "Type Violation in Line " << lineno << " : error: duplicate class: " << className << std::endl;
            type_error = true;
        } else {
            classTable[className] = (*classDeclIter);
        }
    }
    //iterate over classes
    for (auto const& x : classTable) {
        ClassDecl * clptr = x.second;
        currentClass = clptr;
        (clptr)->visit();
    }


    //evaluate MainClass    
    m->visit();
    
    //type errors exist in the program
    if(type_error) {
        exit(1);
    }
    PRINTDEBUG("\n...(Program End Type Check Completed Gracefully) $")
}
void Program::compile() {
    std::string program;
    PRINTDEBUG("\n^ (Program Interpreter Start)...\n")
    
    //ARMS HEADER DATA
    std::string header;
    header += ".section .data\n";
    header += "@ everything here is in the data section\n";
    header += "\n";
    header += ".section .text\n";
    header += "int_print: .asciz \"%d\"\n";
    header += "int_println: .asciz \"%d\\n\"\n";
    
    //Start evaluation of program from MainClass
    m->evaluate();  

    //build program
    //add program default header
    program += header;
        
    //fill out text field
    for(auto const& value: text)
        program += value; 
    program += "\n";

    //unload buffer
    program += buffer;

    //print output 
    PRINTDEBUG("\n...(Program End Run Time Completed Successfully) $")
    std::cout << "ARMS PROGRAM FOLLOWS" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << program << std::endl;

    //Write program to file
    std::ofstream myfile;
    myfile.open("test.s");
    myfile << program;
    myfile.close();
}
