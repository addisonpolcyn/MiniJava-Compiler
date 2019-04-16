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
std::vector<std::string> class_variables;

std::string buffer;
std::vector<std::string> text;

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
void And::evaluate(std::string reg) {
    lhs->evaluate("r0");
    rhs->evaluate("r1");
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
void Or::evaluate(std::string reg) {
    lhs->evaluate("r0");
    rhs->evaluate("r1");
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
void Is::evaluate(std::string reg) {
    //evaluate expr
    lhs->evaluate("r0");
    rhs->evaluate("r1");

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    beq 1f\n";
    buffer += "    ldr "+reg+", =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr "+reg+", =1\n";
    
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
void IsNot::evaluate(std::string reg) {
    //evaluate expr
    lhs->evaluate("r0");
    rhs->evaluate("r1");

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    bne 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";

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
void LessThan::evaluate(std::string reg) {
    //evaluate expr
    lhs->evaluate("r0");
    rhs->evaluate("r1");

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    blt 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";
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
void LessThanEqual::evaluate(std::string reg) {
    //evaluate expr
    lhs->evaluate("r0");
    rhs->evaluate("r1");

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    ble 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";
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
void GreaterThan::evaluate(std::string reg) {
    //evaluate expr
    lhs->evaluate("r0");
    rhs->evaluate("r1");

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    bgt 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";
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
void GreaterThanEqual::evaluate(std::string reg) {
    //evaluate expr
    lhs->evaluate("r0");
    rhs->evaluate("r1");

    //compare equality
    buffer += "    cmp r0, r1\n";
    buffer += "    bge 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";

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
void Plus::evaluate(std::string reg) {
    lhs->evaluate("r0");
    rhs->evaluate("r1");
    buffer += "    add "+reg+", r0, r1\n"; //add values from r0 and r1, store in r0
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
void Minus::evaluate(std::string reg) {
    lhs->evaluate("r0");
    rhs->evaluate("r1");
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
void Times::evaluate(std::string reg) {
    lhs->evaluate("r0");
    rhs->evaluate("r1");
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
void Div::evaluate(std::string reg) {
    //int result = *(int *)lhs->evaluate() / *(int *)rhs->evaluate();
    //void *ptr = &result;
     //
}

ArrayLookup::ArrayLookup(Exp *lhs, Exp *rhs, int lineno): lhs(lhs), rhs(rhs), lineno(lineno) {}
std::string ArrayLookup::visit() {
    PRINTDEBUG("(ArrayLookup)")
    return "int";
}
void ArrayLookup::evaluate(std::string reg) {
    PRINTDEBUG("BROKEN EXPR EVAL")
    int val = 1;
    void *ptr = &val;
     
}

ArrayLength::ArrayLength(Exp *e): e(e) {}
std::string ArrayLength::visit() {
    PRINTDEBUG("(ArrayLength)")
    return "int";
}
void ArrayLength::evaluate(std::string reg) {
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
void Call::evaluate(std::string reg) {
    //get object class and method pointers
    

    
    //ClassDecl *cl = (ClassDecl *)e->evaluate();
    std::string className = currentClass->getName();    
    std::string methodName = i->toString();
    
    //call function
    buffer += "    bl "+className+"_"+methodName+"\n";
    //MethodDecl *method = cl->methods[methodName];
    
    /*
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
void IntegerLiteral::evaluate(std::string reg) {
    int val = num;
    buffer += "    ldr "+reg+", ="+std::to_string(val)+"\n";  //load value into register
}

std::string True::visit() {
    PRINTDEBUG("(True)")
    return "boolean";
}
void True::evaluate(std::string reg) {
    buffer += "    ldr "+reg+", =1\n";  //load value into r0    
}

std::string False::visit() {
    PRINTDEBUG("(False)")
    return "boolean";
}
void False::evaluate(std::string reg) {
    buffer += "    ldr "+reg+", =0\n";  //load value into r0    
}


std::string This::visit() {
    return currentClass->getName();
}
void This::evaluate(std::string reg) {
    ClassDecl *cl = currentClass;
    void *ptr = &(*cl);
}

IdentifierExp::IdentifierExp(std::string str): id(str) {}
std::string IdentifierExp::visit() {
    PRINTDEBUG("(IdentifierExp)")
    return type_local_scope[id]->t->getType();
}
void IdentifierExp::evaluate(std::string reg) {
    PRINTDEBUG("(IdentifierExp)")
    //int val = scope[id];
    //void * ptr = &val;
    int offset = scope[id];

    //load value of var from stack
    buffer += "    add r2, sp, #"+std::to_string(offset)+"\n"; //store the address of sp + offset in r1
    buffer += "    ldr "+reg+", [r2]\n"; //load into r0 the value store at r1 stack location
}

NewArray::NewArray(Exp *e): e(e) {}
std::string NewArray::visit() {
    PRINTDEBUG("(NewArray)")
    return "int []";
}
void NewArray::evaluate(std::string reg) {
    PRINTDEBUG("BROKEN EXPR EVAL")
    int val = 1;
    void *ptr = &val;
}

NewObject::NewObject(Identifier *i): i(i) {}
std::string NewObject::visit() {
    PRINTDEBUG("(NewObject)")
    return i->toString();
}
void NewObject::evaluate(std::string reg) {
    ClassDecl *cl = classTable[i->toString()];
    void *ptr = &(*cl);
    currentClass = cl;
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
void Not::evaluate(std::string reg) {
    e->evaluate("r0");
    
    //compare equality
    buffer += "    cmp r0, #0\n";
    buffer += "    beq 1f\n";
    buffer += "    ldr r0, =0\n";
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    buffer += "    ldr r0, =1\n";
    
    //branch 2
    buffer += "2:      \n";
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
void NegativeExp::evaluate(std::string reg) {
    e->evaluate("r0");
    buffer += "    neg "+reg+","+reg+"\n"; 
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
void PositiveExp::evaluate(std::string reg) {
    e->evaluate("r0");
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
    e->evaluate("r0");

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
    e->evaluate("r0");

    //check if loop should begin
    buffer += "    cmp r0, #1\n";
    buffer += "    beq 1f\n";
    
    //done
    buffer += "    b 2f\n";
    
    //branch 1
    buffer += "1:      \n";
    s->evaluate();
    e->evaluate("r0");
    buffer += "    cmp r0, #1\n";
    buffer += "    beq 1b\n";
    buffer += "    b 2f\n";
    
    //done
    buffer += "2:      \n";
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
    e->evaluate("r0");
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
    e->evaluate("r0");
    buffer += "    mov r1, r0\n";
    buffer += "    ldr r0, =int_println\n";
    buffer += "    bl  printf\n";
}

PrintString::PrintString(std::string str): str(str) {}
void PrintString::visit() {
    PRINTDEBUG("(PrintString)")
}
void PrintString::evaluate() {
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
    std::string id = i->toString();
    int offset = scope[id];
    
    //evaluate expr
    e->evaluate("r0");
    
    std::cout << "assigning at sp+" << offset << " to var:" << id << std::endl;

    //assign onto the stack
    buffer += "    add r1, sp, #"+std::to_string(offset)+"\n";  //store the location sp + offset in r1
    buffer += "    str r0, [r1]\n"; //store the value of r0 on the stack at location r1 (sp + offset)
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
    //prepare function
    buffer += "    push {lr}\n";     
    int offset = 0;
    
    //allocate class variables
    for (auto const& var : class_variables) {
        scope[var] = offset; //offset in stack
        std::cout << "added item:" << var << " to the stack at offset:" << offset << std::endl;
        offset += 4;
    }

    //allocate local variables
    for (auto const& var : localVariables) {
        if(scope.count(var.first) < 1){
            scope[var.first] = offset; //offset in stack
            std::cout << "added item:" << var.first << " to the stack at offset:" << offset << std::endl;
            offset += 4;
        }
    }

    //allocate parameters
    for (auto const& var : parameters) {
        if(scope.count(var.first) < 1){
            scope[var.first] = offset; //offset in stack
            std::cout << "added item:" << var.first << " to the stack at offset:" << offset << std::endl;
            offset += 4;
        }
    }

    //make space for offset
    if(offset)
        buffer += "    sub sp, sp, #"+std::to_string(offset)+"\n";

    //assign parameters
    //TODO

    //evaluate Statement Declarations
    std::list<Statement *>::iterator stmtIter;
    for(stmtIter = sl->begin(); stmtIter != sl->end(); stmtIter++){
        (*stmtIter)->evaluate();
        std::cout << "exectuing statment" << std::endl;
    }
    //int returnVal = *(int *)e->evaluate();
    
    //clean scopes
    //scope.clear();
    //scope_type.clear();
    //void * ptr = &returnVal;
    //evaluate return 
    e->evaluate("r0");
    
    //restore stack pointer to original location before function
    if(offset)
        buffer += "    add sp, sp, #"+std::to_string(offset)+"\n";

    //return program counter
    buffer += "    pop {pc}\n";

    //return branch stmt
    buffer += "    bx lr\n";     

    //clean scope
    scope.clear();
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
void ClassDeclSimple::evaluate() {
    //check formal variables
    //TODO upodate the class scope
    for (auto const& variable : fieldVariables) {
        class_variables.push_back(variable.first);
    }

    //iterate over methods
    for (auto const& method : methods) {
        buffer += "\n"+i->toString()+"_"+method.first+":\n";
        (method.second)->evaluate();
    }
}
std::string ClassDeclSimple::getName() {
    return i->toString();
}

ClassDeclExtends::ClassDeclExtends(Identifier *i, Identifier *j, std::list<VarDecl *> *vl, std::list<MethodDecl *> *ml, int lineno): i(i), j(j), vl(vl), ml(ml), lineno(lineno) {}
void ClassDeclExtends::visit() {
    PRINTDEBUG("(ClassDeclExtends)")
}
void ClassDeclExtends::evaluate() {
    //TODO
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
    //string buffer to hold ARM Program
    std::string program;
    
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

    //iterate over classes to build functions
    for (auto const& x : classTable) {
        ClassDecl * clptr = x.second;
        currentClass = clptr;
        (clptr)->evaluate();
    }

    //build program
    program += header;
        
    //fill out text field
    for(auto const& value: text)
        program += value; 
    program += "\n";

    //unload buffer
    program += buffer;

    //Write program to file
    std::ofstream myfile;
    myfile.open("test.s");
    myfile << program;
    myfile.close();

    //print output 
    PRINTDEBUG("\n...(Program End Run Time Completed Successfully) $")
    std::cout << "ARMS PROGRAM FOLLOWS" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << program << std::endl;
}
