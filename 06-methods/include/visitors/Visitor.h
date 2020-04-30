#pragma once

#include "forward_decl.h"

class Visitor {
 public:
    virtual void Visit(SimpleType* simple_type) = 0;
    virtual void Visit(ArrayType* array_type) = 0;
    virtual void Visit(AssertStatement* assert_statement) = 0;
    virtual void Visit(AssignmentStatement* assignment_statement) = 0;
    virtual void Visit(IfStatement* if_statement) = 0;
    virtual void Visit(IfElseStatement* if_else_statement) = 0;
    virtual void Visit(LocalVariableDeclaration* local_variable_declaration) = 0;
    virtual void Visit(LocalVariableDeclarationStatement* local_variable_declaration_statement) = 0;
    virtual void Visit(MethodInvocationStatement* method_invocation_statement) = 0;
    virtual void Visit(ReturnStatement* return_statement) = 0;
    virtual void Visit(ScopeStatement* scope_statement) = 0;
    virtual void Visit(SoutStatement* sout_statement) = 0;
    virtual void Visit(Statement* statement) = 0;
    virtual void Visit(StatementList* statement_list) = 0;
    virtual void Visit(WhileStatement* while_statement) = 0;
    virtual void Visit(Lvalue* lvalue) = 0;
    virtual void Visit(SimpleLvalue* simple_lvalue) = 0;
    virtual void Visit(ArrayElementLvalue* array_element_lvalue) = 0;
    virtual void Visit(AccessToArrayElementExpression* access_to_array_element_expression) = 0;
    virtual void Visit(ArrayDefenitionExpression* array_defenition_expression) = 0;
    virtual void Visit(ArrayLengthExpression* array_length_expression) = 0;
    virtual void Visit(BinaryOperatorExpression* binary_operator_expression) = 0;
    virtual void Visit(DefenitionExpression* defenition_expression) = 0;
    virtual void Visit(Expression* expression) = 0;
    virtual void Visit(ExpressionList* expression_list) = 0;
    virtual void Visit(IdentExpression* ident_expression) = 0;
    virtual void Visit(MethodInvocationExpression* method_invocation_expression) = 0;
    virtual void Visit(NotExpression* not_expression) = 0;
    virtual void Visit(NumberExpression* number_expression) = 0;
    virtual void Visit(ParenthesisExpression* parenthesis_expression) = 0;
    virtual void Visit(ThisExpression* this_expression) = 0;
    virtual void Visit(BoolExpression* bool_expression) = 0;
    virtual void Visit(Declaration* declaration) = 0;
    virtual void Visit(DeclarationList* declaration_list) = 0;
    virtual void Visit(MethodDeclaration* method_declaration) = 0;
    virtual void Visit(VariableDeclaration* variable_declaration) = 0;
    virtual void Visit(ClassDeclaration* class_declaration) = 0;
    virtual void Visit(ClassDeclarationList* class_declaration_list) = 0;
    virtual void Visit(MainClass* main_class) = 0;
    virtual void Visit(Type* type) = 0;
    virtual void Visit(TypeIdentifier* type_identifier) = 0;
    virtual void Visit(MethodInvocation* method_invocation) = 0;
    virtual void Visit(FormalList* formal_list) = 0;
    virtual void Visit(Formal* formal) = 0;
    virtual void Visit(BinaryOperator* binary_operator) = 0;
    virtual void Visit(Program* program) = 0;
};
