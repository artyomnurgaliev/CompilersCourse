//
// Created by Pavel Akhtyamov on 25.03.2020.
//

#include <iostream>
#include <method-mechanisms/FunctionStorage.h>
#include "MethodCallVisitor.h"

#include "elements.h"

void MethodCallVisitor::Visit(SimpleType* simple_type){
  /// do nothing
}
void MethodCallVisitor::Visit(ArrayType* array_type) {
  /// do nothing
}
void MethodCallVisitor::Visit(AssertStatement* assert_statement){
  assert_statement->GetExpression()->Accept(this);
}
void MethodCallVisitor::Visit(AssignmentStatement* assignment_statement) {
  assignment_statement->GetExpression()->Accept(this);
  PrimitiveObjectType* tos_type = tos_type_;

  assignment_statement->GetLvalue()->Accept(this);
}
void MethodCallVisitor::Visit(IfStatement* if_statement) {}
void MethodCallVisitor::Visit(IfElseStatement* if_else_statement){}
void MethodCallVisitor::Visit(LocalVariableDeclaration* local_variable_declaration){}
void MethodCallVisitor::Visit(MethodInvocationStatement* method_invocation_statement) {}
void MethodCallVisitor::Visit(ReturnStatement* return_statement) {}
void MethodCallVisitor::Visit(ScopeStatement* scope_statement) {}
void MethodCallVisitor::Visit(SoutStatement* sout_statement){}
void MethodCallVisitor::Visit(StatementList* statement_list){}
void MethodCallVisitor::Visit(WhileStatement* while_statement) {}
void MethodCallVisitor::Visit(SimpleLvalue* simple_lvalue) {}
void MethodCallVisitor::Visit(ArrayElementLvalue* array_element_lvalue) {}
void MethodCallVisitor::Visit(AccessToArrayElementExpression* access_to_array_element_expression){}
void MethodCallVisitor::Visit(ArrayNewExpression* array_defenition_expression) {}
void MethodCallVisitor::Visit(ArrayLengthExpression* array_length_expression){}
void MethodCallVisitor::Visit(BinaryOperatorExpression* binary_operator_expression){}
void MethodCallVisitor::Visit(NewExpression* defenition_expression) {}
void MethodCallVisitor::Visit(ExpressionList* expression_list){}
void MethodCallVisitor::Visit(IdentExpression* ident_expression) {}
void MethodCallVisitor::Visit(MethodInvocationExpression* method_invocation_expression){}
void MethodCallVisitor::Visit(NotExpression* not_expression) {}
void MethodCallVisitor::Visit(NumberExpression* number_expression) {}
void MethodCallVisitor::Visit(ParenthesisExpression* parenthesis_expression) {}
void MethodCallVisitor::Visit(ThisExpression* this_expression) {}
void MethodCallVisitor::Visit(BoolExpression* bool_expression) {}
void MethodCallVisitor::Visit(Declaration* declaration) {}
void MethodCallVisitor::Visit(DeclarationList* declaration_list) {}
void MethodCallVisitor::Visit(MethodDeclaration* method_declaration) {}
void MethodCallVisitor::Visit(VariableDeclaration* variable_declaration) {}
void MethodCallVisitor::Visit(ClassDeclaration* class_declaration) {}
void MethodCallVisitor::Visit(ClassDeclarationList* class_declaration_list) {}
void MethodCallVisitor::Visit(MainClass* main_class) {}
void MethodCallVisitor::Visit(Type* type) {}
void MethodCallVisitor::Visit(TypeIdentifier* type_identifier) {}
void MethodCallVisitor::Visit(MethodInvocation* method_invocation) {}
void MethodCallVisitor::Visit(FormalList* formal_list) {}
void MethodCallVisitor::Visit(Formal* formal) {}
void MethodCallVisitor::Visit(BinaryOperator* binary_operator) {}
void MethodCallVisitor::Visit(Program* program) {}
void MethodCallVisitor::Visit(Expression *expression) {}
void MethodCallVisitor::Visit(Lvalue *lvalue) {}
void MethodCallVisitor::Visit(Statement *statement) {}
void MethodCallVisitor::Visit(LocalVariableDeclarationStatement *local_variable_declaration_statement) {
}




void MethodCallVisitor::Visit(NumberExpression *expression) {
  tos_value_ = expression->value_;
}

void MethodCallVisitor::Visit(AddExpression *expression) {
  tos_value_ = Accept(expression->first) + Accept(expression->second);
}

void MethodCallVisitor::Visit(SubstractExpression *expression) {
  tos_value_ = Accept(expression->first) - Accept(expression->second);
}

void MethodCallVisitor::Visit(MulExpression *expression) {
  tos_value_ = Accept(expression->first) * Accept(expression->second);
}

void MethodCallVisitor::Visit(DivExpression *expression) {
  tos_value_ = Accept(expression->first) / Accept(expression->second);
}

void MethodCallVisitor::Visit(IdentExpression *expression) {
  int index = table_.Get(Symbol(expression->ident_));
  tos_value_ = frame.Get(index);
}

void MethodCallVisitor::Visit(Assignment *assignment) {
  int value = Accept(assignment->expression_);

  int index = table_.Get(Symbol(assignment->variable_));
  frame.Set(index, value);
}

void MethodCallVisitor::Visit(VarDecl *var_decl) {
  size_t index = frame.AllocVariable();
  table_.CreateVariable(Symbol(var_decl->variable_));
  table_.Put(Symbol(var_decl->variable_), index);

}

void MethodCallVisitor::Visit(PrintStatement *statement) {
  int value = Accept(statement->expression_);

  std::cout << value << std::endl;
}

void MethodCallVisitor::Visit(AssignmentList *assignment_list) {
  for (Statement* assignment: assignment_list->statements_) {
      if (!returned_) {
          assignment->Accept(this);
      }
  }
}

void MethodCallVisitor::Visit(ScopeAssignmentList *list) {
  std::cout << "Going inside" << std::endl;

  current_layer_ = current_layer_->GetChild(offsets_.top());

  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();
  list->statement_list->Accept(this);

  offsets_.pop();
  size_t index = offsets_.top();

  offsets_.pop();
  offsets_.push(index + 1);

  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
}

void MethodCallVisitor::Visit(Program *program) {

}

void MethodCallVisitor::Visit(ParamList *param_list) {
    int index = -1;
    for (auto param: param_list->params_) {
        table_.CreateVariable(Symbol(param));
        table_.Put(Symbol(param), index);
        --index;
    }
}

void MethodCallVisitor::Visit(Function *function) {
    function->param_list_->Accept(this);
  function->statements_->Accept(this);
}

MethodCallVisitor::MethodCallVisitor(
    ScopeLayer* function_scope, std::shared_ptr<FunctionType> function
    ) : root_layer(function_scope), frame(function) {
  current_layer_ = root_layer;
  offsets_.push(0);
  tos_value_ = 0;
}

void MethodCallVisitor::SetParams(const std::vector<int> &params) {
  frame.SetParams(params);
}

void MethodCallVisitor::Visit(FunctionCallExpression *statement) {
  std::cerr << "Function called " << statement->name_ << std::endl;
  auto function_type = current_layer_->Get(statement->name_);

  std::shared_ptr<FunctionType> func_converted = std::dynamic_pointer_cast<FunctionType>(function_type);

  if (func_converted == nullptr) {
    throw std::runtime_error("Function not defined");
  }

  std::vector<int> params;

  for (auto param : statement->param_list_->params_) {
      params.push_back(Accept(param));
  }

  MethodCallVisitor new_visitor(
      tree_->GetFunctionScopeByName(statement->name_),
      func_converted
  );
  new_visitor.SetParams(params);

  new_visitor.GetFrame().SetParentFrame(&frame);
  new_visitor.Visit(FunctionStorage::GetInstance().Get(Symbol(statement->name_)));


  tos_value_ = frame.GetReturnValue();
}

void MethodCallVisitor::Visit(FunctionList *function_list) {

}

void MethodCallVisitor::Visit(ParamValueList *value_list) {

}

void MethodCallVisitor::Visit(ReturnStatement *return_statement) {
    if (frame.HasParent()) {
        frame.SetParentReturnValue(Accept(return_statement->return_expression_));
    }
    returned_ = true;
}

void MethodCallVisitor::SetTree(ScopeLayerTree *tree) {
    tree_ = tree;

}

Frame &MethodCallVisitor::GetFrame() {
    return frame;
}
