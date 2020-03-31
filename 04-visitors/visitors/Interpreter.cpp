#include "Interpreter.h"

#include "elements.h"

#include <iostream>

Interpreter::Interpreter() {
    variables_["one"] = 1;
    variables_["two"] = 2;
    is_tos_expression_ = false;
    tos_value_ = 0;
}

void Interpreter::Visit(SimpleType* simple_type){}
void Interpreter::Visit(ArrayType* array_type) {}
void Interpreter::Visit(AssertStatement* assert_statement){}
void Interpreter::Visit(AssignmentStatement* assignment_statement) {}
void Interpreter::Visit(IfStatement* if_statement) {}
void Interpreter::Visit(IfElseStatement* if_else_statement){}
void Interpreter::Visit(LocalVariableDeclaration* local_variable_declaration){}
void Interpreter::Visit(MethodInvocationStatement* method_invocation_statement) {}
void Interpreter::Visit(ReturnStatement* return_statement) {}
void Interpreter::Visit(ScopeStatement* scope_statement) {}
void Interpreter::Visit(SoutStatement* sout_statement){}
void Interpreter::Visit(StatementList* statement_list){}
void Interpreter::Visit(WhileStatement* while_statement) {}
void Interpreter::Visit(SimpleLvalue* simple_lvalue) {}
void Interpreter::Visit(ArrayElementLvalue* array_element_lvalue) {}
void Interpreter::Visit(AccessToArrayElementExpression* access_to_array_element_expression){}
void Interpreter::Visit(ArrayDefenitionExpression* array_defenition_expression) {}
void Interpreter::Visit(ArrayLengthExpression* array_length_expression){}
void Interpreter::Visit(BinaryOperatorExpression* binary_operator_expression){}
void Interpreter::Visit(DefenitionExpression* defenition_expression) {}
void Interpreter::Visit(ExpressionList* expression_list){}
void Interpreter::Visit(IdentExpression* ident_expression) {}
void Interpreter::Visit(MethodInvocationExpression* method_invocation_expression){}
void Interpreter::Visit(NotExpression* not_expression) {}
void Interpreter::Visit(NumberExpression* number_expression) {}
void Interpreter::Visit(ParenthesisExpression* parenthesis_expression) {}
void Interpreter::Visit(ThisExpression* this_expression) {}
void Interpreter::Visit(BoolExpression* bool_expression) {}
void Interpreter::Visit(Declaration* declaration) {}
void Interpreter::Visit(DeclarationList* declaration_list) {}
void Interpreter::Visit(MethodDeclaration* method_declaration) {}
void Interpreter::Visit(VariableDeclaration* variable_declaration) {}
void Interpreter::Visit(ClassDeclaration* class_declaration) {}
void Interpreter::Visit(ClassDeclarationList* class_declaration_list) {}
void Interpreter::Visit(MainClass* main_class) {}
void Interpreter::Visit(Type* type) {}
void Interpreter::Visit(TypeIdentifier* type_identifier) {}
void Interpreter::Visit(MethodInvocation* method_invocation) {}
void Interpreter::Visit(FormalList* formal_list) {}
void Interpreter::Visit(Formal* formal) {}
void Interpreter::Visit(BinaryOperator* binary_operator) {}
void Interpreter::Visit(Program* program) {}
void Interpreter::Visit(Expression *expression) {}
void Interpreter::Visit(Lvalue *lvalue) {}
void Interpreter::Visit(Statement *statement) {}
void Interpreter::Visit(
    LocalVariableDeclarationStatement *local_variable_declaration_statement) {

}
/*

void Interpreter::Visit(NumberExpression* expression) {
    SetTosValue(expression->value_);
}

void Interpreter::Visit(AddExpression* expression) {
    int value = 0;
    expression->first->Accept(this);
    value += tos_value_;

    expression->second->Accept(this);
    value += tos_value_;
    SetTosValue(value);
}

void Interpreter::Visit(SubstractExpression* expression) {
    expression->first->Accept(this);
    int value = tos_value_;
    expression->second->Accept(this);
    value -= tos_value_;
    
    SetTosValue(value);
}

void Interpreter::Visit(MulExpression* expression) {
    expression->first->Accept(this);
    int value = tos_value_;
    expression->second->Accept(this);
    value *= tos_value_;
    
    SetTosValue(value);
}

void Interpreter::Visit(DivExpression* expression) {
    expression->first->Accept(this);
    int value = tos_value_;
    expression->second->Accept(this);
    value /= tos_value_;

    SetTosValue(value);
}

void Interpreter::Visit(IdentExpression* expression) {
    int value = variables_[expression->identifier_];

    SetTosValue(value);
}

void Interpreter::Visit(Assignment* assignment) {
    assignment->expression_->Accept(this);
    variables_[assignment->variable_] = tos_value_;

    UnsetTosValue();
}

void Interpreter::Visit(AssignmentList* assignment_list) {
    for (Assignment* assignment: assignment_list->assignments_) {
        assignment->Accept(this);
    }
    UnsetTosValue();
}

void Interpreter::Visit(Program* program) {
    program->assignments_->Accept(this);
    
    program->expression_->Accept(this); // tos value is called
}
*/

void Interpreter::SetTosValue(int value) {
    tos_value_ = value;
    is_tos_expression_ = true;
}

void Interpreter::UnsetTosValue() {
    tos_value_ = 0;
    is_tos_expression_ = false;
}

int Interpreter::GetResult(Program *program) {
    UnsetTosValue();
    Visit(program);
    return tos_value_;
}

