//
// Created by Pavel Akhtyamov on 25.03.2020.
//

#include <iostream>
#include <method-mechanisms/ClassStorage.h>
#include <objects/objs/ArrayObject.h>
#include <objects/objs/VariableObject.h>
#include "MethodCallVisitor.h"

#include "elements.h"
MethodCallVisitor::MethodCallVisitor(ScopeLayer *method_scope, const std::shared_ptr<MethodType>& method, VariableObject* object) :
  root_layer(method_scope),
  frame(method->GetMethodDeclaration()->GetFormals()->GetSize()),
  this_(object){
  current_layer_ = root_layer;
  offsets_.push(0);
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("int")),
      0);
  std::vector<Object*> fields;
  int index = -1;
  for (const auto &field : object->) {
    fields.push_back(field.second);
    table_.CreateVariable(field.first);
    table_.Put(field.first, index);
    --index;
  }
  frame.SetFields(fields);
}

void MethodCallVisitor::Visit(SimpleType *simple_type) {
  /// do nothing
}
void MethodCallVisitor::Visit(ArrayType *array_type) {
  /// do nothing
}
void MethodCallVisitor::Visit(AssertStatement *assert_statement) {
  if (!Accept(assert_statement->GetExpression())->GetValue()) {
    throw std::runtime_error("Assert failed");
  }
}
void MethodCallVisitor::Visit(AssignmentStatement *assignment_statement) {
  auto result = Accept(assignment_statement->GetExpression());
  int index = table_.Get(Symbol(assignment_statement->GetLvalue()->GetIdentifier()));
  if (assignment_statement->GetLvalue()->IsSimple()) {
    frame.Set(index, result);
  } else {
    int index_in_array = Accept(assignment_statement->GetLvalue())->GetValue();
    dynamic_cast<ArrayObject *>(frame.Get(index))->SetAtIndex(result, index_in_array);
  }

}
void MethodCallVisitor::Visit(IfStatement *if_statement) {
  if (Accept(if_statement->GetExpression())->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    if_statement->GetStatement()->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
}
void MethodCallVisitor::Visit(IfElseStatement *if_else_statement) {
  if (Accept(if_else_statement->GetExpression())->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    if_else_statement->GetStatement()->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 2);
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  } else {
    current_layer_ = current_layer_->GetChild(offsets_.top() + 1);
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    if_else_statement->GetElseStatement()->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 2);
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
}
void MethodCallVisitor::Visit(LocalVariableDeclaration *local_variable_declaration) {
  local_variable_declaration->GetVariableDeclaration()->Accept(this);
}
void MethodCallVisitor::Visit(MethodInvocationStatement *method_invocation_statement) {
  method_invocation_statement->GetMethodInvocation()->Accept(this);
}
void MethodCallVisitor::Visit(ReturnStatement *return_statement) {
  if (frame.HasParent()) {
    frame.SetParentReturnValue(Accept(return_statement->GetExpression()));
  }
  returned_ = true;
}
void MethodCallVisitor::Visit(ScopeStatement *scope_statement) {
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();
  scope_statement->GetStatementList()->Accept(this);
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
}
void MethodCallVisitor::Visit(SoutStatement *sout_statement) {
  std::cout << Accept(sout_statement->GetExpression())->GetValue() << std::endl;
}
void MethodCallVisitor::Visit(StatementList *statement_list) {
  for (auto st: statement_list->GetStatements()) {
    st->Accept(this);
  }
}
void MethodCallVisitor::Visit(WhileStatement *while_statement) {
  while (Accept(while_statement->GetExpression())->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    while_statement->GetStatement()->Accept(this);
    offsets_.pop();
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}
void MethodCallVisitor::Visit(SimpleLvalue *simple_lvalue) {
  /// do nothing
}
void MethodCallVisitor::Visit(ArrayElementLvalue *array_element_lvalue) {
  tos_value_ = Accept(array_element_lvalue->GetExpression());
}
void MethodCallVisitor::Visit(AccessToArrayElementExpression *access_to_array_element_expression) {
  int index = Accept(access_to_array_element_expression->GetSecond())->GetValue();
  tos_value_ = dynamic_cast<ArrayObject *>(Accept(access_to_array_element_expression->GetFirst()))->AtIndex(index);
}
void MethodCallVisitor::Visit(ArrayNewExpression *array_new_expression) {
  auto new_arr =
    new ArrayObject(
      new PrimitiveArrayType(
        new PrimitiveSimpleType(array_new_expression->GetSimpleType())));
  size_t size = Accept(array_new_expression->GetExpression())->GetValue();
  new_arr->Resize(size);
  tos_value_ = new_arr;
}
void MethodCallVisitor::Visit(ArrayLengthExpression *array_length_expression) {
  auto arr = Accept(array_length_expression->GetExpression());
  int size = dynamic_cast<ArrayObject *>(arr)->GetSize();
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("int")), size);
}
void MethodCallVisitor::Visit(BinaryOperatorExpression *binary_operator_expression) {
  auto leftobj = Accept(binary_operator_expression->GetFirst());
  auto rightobj = Accept(binary_operator_expression->GetSecond());
  auto left_type = leftobj->GetType()->GetTypeName();
  auto right_type = rightobj->GetType()->GetTypeName();

  auto left = leftobj->GetValue();
  auto right = rightobj->GetValue();
  if (left_type != right_type) {
    throw std::runtime_error("Different types of binary expression parts");
  }
  if (left_type != "int" && left_type != "boolean") {
    throw std::runtime_error("Strange type for binary expression");
  }
  auto op = binary_operator_expression->GetBinaryOperator()->GetOperatorName();
  std::string result_type;
  int result;
  if (op == "&&") {
    result = left && right;
    result_type = "boolean";
  }
  if (op == "||") {
    result = left || right;
    result_type = "boolean";
  }
  if (op == "<") {
    result = left < right;
    result_type = "boolean";
  }
  if (op == ">") {
    result = left > right;
    result_type = "boolean";
  }
  if (op == "==") {
    result = left == right;
    result_type = "boolean";
  }
  if (op == "+") {
    result = left + right;
    result_type = "int";
  }
  if (op == "-") {
    result = left - right;
    result_type = "int";
  }
  if (op == "*") {
    result = left * right;
    result_type = "int";
  }
  if (op == "/") {
    result = left / right;
    result_type = "int";
  }
  if (op == "%") {
    result = left % right;
    result_type = "int";
  }

  tos_value_ = new VariableObject(new PrimitiveSimpleType(new SimpleType(result_type)), result);
}
void MethodCallVisitor::Visit(NewExpression *new_expression) {
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType(new_expression->GetTypeIdentifier())));
}
void MethodCallVisitor::Visit(ExpressionList *expression_list) {
  /// do nothing (it is params in method invocation)
}
void MethodCallVisitor::Visit(IdentExpression *ident_expression) {
  int index = table_.Get(Symbol(ident_expression->GetIdentifier()));
  tos_value_ = frame.Get(index);
}
void MethodCallVisitor::Visit(MethodInvocationExpression *method_invocation_expression) {
  tos_value_ = Accept(method_invocation_expression->GetMethodInvocation());
}
void MethodCallVisitor::Visit(NotExpression *not_expression) {
  int result = Accept(not_expression->GetExpression())->GetValue();
  result = !result;
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("boolean")), result);
}
void MethodCallVisitor::Visit(NumberExpression *number_expression) {
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("int")),
    number_expression->GetValue());
}
void MethodCallVisitor::Visit(ParenthesisExpression *parenthesis_expression) {
  tos_value_ = Accept(parenthesis_expression->GetExpression());
}
void MethodCallVisitor::Visit(ThisExpression *this_expression) {
  tos_value_ = this_;
}
void MethodCallVisitor::Visit(BoolExpression *bool_expression) {
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("boolean")),
    bool_expression->GetValue());
}
void MethodCallVisitor::Visit(Declaration *declaration) {
  if (declaration->IsVariable()) {
    declaration->GetVariableDeclaration()->Accept(this);
  } else {
    declaration->GetMethodDeclaration()->Accept(this);
  }
}
void MethodCallVisitor::Visit(DeclarationList *declaration_list) {
  for (auto d: declaration_list->GetDeclarations()) {
    d->Accept(this);
  }
}
void MethodCallVisitor::Visit(MethodDeclaration *method_declaration) {
  method_declaration->GetFormals()->Accept(this);
  method_declaration->GetStatements()->Accept(this);
}
void MethodCallVisitor::Visit(VariableDeclaration *variable_declaration) {
  size_t index;
  if (variable_declaration->GetType()->IsSimpleType()) {
    index = frame.AllocVariable(new PrimitiveSimpleType(
      variable_declaration->GetType()->GetSimpleType()));
  } else {
    index = frame.AllocVariable(new PrimitiveArrayType(
      variable_declaration->GetType()->GetArrayType()));
  }
  table_.CreateVariable(Symbol(variable_declaration->GetIdentifier()));
  table_.Put(Symbol(variable_declaration->GetIdentifier()), index);
}
void MethodCallVisitor::Visit(ClassDeclaration *class_declaration) {
  /// do nothing
}
void MethodCallVisitor::Visit(ClassDeclarationList *class_declaration_list) {
  /// do nothing
}
void MethodCallVisitor::Visit(MainClass *main_class) {
  main_class->GetStatementList()->Accept(this);
}
void MethodCallVisitor::Visit(Type *type) {
  /// do nothing
}
void MethodCallVisitor::Visit(TypeIdentifier *type_identifier) {
  /// do nothing
}
void MethodCallVisitor::Visit(MethodInvocation *method_invocation) {

}

void MethodCallVisitor::Visit(FormalList *formal_list) {
  int index = -frame.GetFieldsSize() - 1;
  for (auto formal : formal_list->GetFormals()) {
    table_.CreateVariable(Symbol(formal->GetIdentifier()));
    table_.Put(Symbol(formal->GetIdentifier()), index);
    --index;
  }
}
void MethodCallVisitor::Visit(Formal *formal) {
  /// realization in formal_list
}
void MethodCallVisitor::Visit(BinaryOperator *binary_operator) {
  /// do nothing
}
void MethodCallVisitor::Visit(Program *program) {
  /// do nothing, because Visitor starts from "main"
}
void MethodCallVisitor::Visit(Expression *expression) {
  /// do nothing
}
void MethodCallVisitor::Visit(Lvalue *lvalue) {
  /// do nothing
}
void MethodCallVisitor::Visit(Statement *statement) {
  /// do nothing
}
void MethodCallVisitor::Visit(LocalVariableDeclarationStatement *local_variable_declaration_statement) {
  local_variable_declaration_statement->GetLocalVariableDeclaration()->Accept(this);
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
  for (Statement *assignment: assignment_list->statements_) {
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
  new_visitor.Visit(ClassStorage::GetInstance().GetMethods(Symbol(statement->name_)));

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
