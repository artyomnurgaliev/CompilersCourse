#include "include/visitors/Visitor.h"

#include <map>

class  : public Visitor {
 public:
    Interpreter();
    void Visit(SimpleType* simple_type)override;
    void Visit(ArrayType* array_type) override;
    void Visit(AssertStatement* assert_statement)override;
    void Visit(AssignmentStatement* assignment_statement) override;
    void Visit(IfStatement* if_statement) override;
    void Visit(IfElseStatement* if_else_statement) override;
    void Visit(LocalVariableDeclaration* local_variable_declaration) override;
    void Visit(LocalVariableDeclarationStatement* local_variable_declaration_statement) override;
    void Visit(MethodInvocationStatement* method_invocation_statement) override;
    void Visit(ReturnStatement* return_statement) override;
    void Visit(ScopeStatement* scope_statement) override;
    void Visit(SoutStatement* sout_statement)override;
    void Visit(Statement* statement) override;
    void Visit(StatementList* statement_list) override;
    void Visit(WhileStatement* while_statement) override;
    void Visit(Lvalue* lvalue) override;
    void Visit(SimpleLvalue* simple_lvalue) override;
    void Visit(ArrayElementLvalue* array_element_lvalue) override;
    void Visit(AccessToArrayElementExpression* access_to_array_element_expression) override;
    void Visit(ArrayNewExpression* array_defenition_expression) override;
    void Visit(ArrayLengthExpression* array_length_expression) override;
    void Visit(BinaryOperatorExpression* binary_operator_expression)override;
    void Visit(NewExpression* defenition_expression) override;
    void Visit(Expression* expression) override;
    void Visit(ExpressionList* expression_list)override;
    void Visit(IdentExpression* ident_expression) override;
    void Visit(MethodInvocationExpression* method_invocation_expression) override;
    void Visit(NotExpression* not_expression) override;
    void Visit(NumberExpression* number_expression) override;
    void Visit(ParenthesisExpression* parenthesis_expression) override;
    void Visit(ThisExpression* this_expression)override;
    void Visit(BoolExpression* bool_expression) override;
    void Visit(Declaration* declaration)override;
    void Visit(DeclarationList* declaration_list) override;
    void Visit(MethodDeclaration* method_declaration) override;
    void Visit(VariableDeclaration* variable_declaration)override;
    void Visit(ClassDeclaration* class_declaration) override;
    void Visit(ClassDeclarationList* class_declaration_list) override;
    void Visit(MainClass* main_class) override;
    void Visit(Type* type)override;
    void Visit(TypeIdentifier* type_identifier)override;
    void Visit(MethodInvocation* method_invocation) override;
    void Visit(FormalList* formal_list)override;
    void Visit(Formal* formal)override;
    void Visit(BinaryOperator* binary_operator)override;
    void Visit(Program* program) override;

    int GetResult(Program* program);

 private:
    std::map<std::string, int> variables_;
    bool is_tos_expression_;
    int tos_value_;

    void SetTosValue(int value);
    void UnsetTosValue();
    
};