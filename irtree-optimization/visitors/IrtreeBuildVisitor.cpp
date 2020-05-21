#include "IrtreeBuildVisitor.h"

#include "elements.h"
#include <objects/objs_creation/ObjectCreation.h>
#include <method-mechanisms/ClassStorage.h>
#include <irtree/tree_wrapper/ExpressionWrapper.h>
#include <irtree/tree_wrapper/StatementWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/NegateConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/OrConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/AndConditionalWrapper.h>

#include <irtree/nodes/statements/LabelStatement.h>
#include <irtree/nodes/statements/JumpStatement.h>

IrtMapping IrtreeBuildVisitor::GetTrees() {
  return method_trees_;
}
void IrtreeBuildVisitor::Visit(SimpleType *simple_type) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(ArrayType *array_type) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(AssertStatement *assert_statement) {
  auto *irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(Accept(assert_statement->GetExpression())->ToExpression());
  tos_value_ = new IRT::ExpressionWrapper(new IRT::CallExpression(
    new IRT::NameExpression(IRT::Label("assert")),
    irt_expressions));
  /// TODO(later) - add label assert
}
void IrtreeBuildVisitor::Visit(AssignmentStatement *assignment_statement) {
  auto var_expression = Accept(assignment_statement->GetLvalue())->ToExpression();
  auto rvalue = Accept(assignment_statement->GetExpression());

  tos_value_ = new IRT::StatementWrapper(new IRT::MoveStatement(
    var_expression,
    rvalue->ToExpression())
  );
}

void IrtreeBuildVisitor::Visit(IfStatement *if_statement) {
  auto if_cond_expression = Accept(if_statement->GetExpression());

  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  current_frame_->SetupScope();
  auto true_stmt = Accept(if_statement->GetStatement());
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_join;

  IRT::Statement *suffix = new IRT::LabelStatement(label_join);

  IRT::Label *result_true = &label_join;
  IRT::Label *result_false = &label_join;

  if (true_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
      new IRT::LabelStatement(label_true),
      new IRT::SeqStatement(true_stmt->ToStatement(),
                            new IRT::SeqStatement(new IRT::JumpStatement(label_join), suffix))
    );
  }

  tos_value_ = new IRT::StatementWrapper(
    new IRT::SeqStatement(
      if_cond_expression->ToConditional(*result_true, *result_false),
      suffix
    )
  );
}
void IrtreeBuildVisitor::Visit(IfElseStatement *if_else_statement) {
  auto if_cond_expression = Accept(if_else_statement->GetExpression());
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  current_frame_->SetupScope();
  auto true_stmt = Accept(if_else_statement->GetStatement());
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  current_frame_->TearDownScope();

  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  current_frame_->SetupScope();
  auto false_stmt = Accept(if_else_statement->GetElseStatement());
  offsets_.pop();
  index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_false;
  IRT::Label label_join;

  IRT::Statement *suffix = new IRT::LabelStatement(label_join);

  IRT::Label *result_true = &label_join;
  IRT::Label *result_false = &label_join;

  if (false_stmt) {
    result_false = &label_false;
    suffix = new IRT::SeqStatement(
      new IRT::LabelStatement(label_false),
      new IRT::SeqStatement(false_stmt->ToStatement(), suffix)
    );

    if (true_stmt) {
      suffix = new IRT::SeqStatement(
        new IRT::JumpStatement(label_join),
        suffix
      );
    }
  }

  if (true_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
      new IRT::LabelStatement(label_true),
      new IRT::SeqStatement(true_stmt->ToStatement(), suffix)
    );
  }

  tos_value_ = new IRT::StatementWrapper(
    new IRT::SeqStatement(
      if_cond_expression->ToConditional(*result_true, *result_false),
      suffix
    )
  );
}
void IrtreeBuildVisitor::Visit(LocalVariableDeclaration *local_variable_declaration) {
  local_variable_declaration->GetVariableDeclaration()->Accept(this);
}
void IrtreeBuildVisitor::Visit(MethodInvocationStatement *method_invocation_statement) {
  method_invocation_statement->GetMethodInvocation()->Accept(this);
}

void IrtreeBuildVisitor::Visit(ReturnStatement *return_statement) {
  auto return_expr = Accept(return_statement->GetExpression());
  tos_value_ = new IRT::StatementWrapper(
    new IRT::MoveStatement(
      current_frame_->GetReturnValueAddress(),
      return_expr->ToExpression()
    )
  );
}
void IrtreeBuildVisitor::Visit(ScopeStatement *scope_statement) {
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  current_frame_->SetupScope();
  tos_value_ = Accept(scope_statement->GetStatementList());
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  current_frame_->TearDownScope();
}
void IrtreeBuildVisitor::Visit(SoutStatement *sout_statement) {
  auto *irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(Accept(sout_statement->GetExpression())->ToExpression());
  tos_value_ = new IRT::ExpressionWrapper(new IRT::CallExpression(
    new IRT::NameExpression(IRT::Label("print")),
    irt_expressions));
  /// TODO(later) - add label 'print'
}
void IrtreeBuildVisitor::Visit(StatementList *statement_list) {
  if (statement_list->GetStatements().empty()) {
    tos_value_ = nullptr;
    return;
  }

  if (statement_list->GetStatements().size() == 1) {
    tos_value_ = Accept(statement_list->GetStatements()[0]);
  } else {
    std::vector<IRT::Statement *> statements;
    statements.reserve(statement_list->GetStatements().size());
    for (auto statement: statement_list->GetStatements()) {
      auto stmt = Accept(statement);
      if (stmt) {
        statements.push_back(stmt->ToStatement());
      }
    }
    IRT::Statement *suffix = statements.back();

    for (int index = static_cast<int>(statements.size()) - 2; index >= 0; --index) {
      suffix = new IRT::SeqStatement(
        statements.at(index),
        suffix
      );
    }
    tos_value_ = new IRT::StatementWrapper(suffix);
  }
}
void IrtreeBuildVisitor::Visit(WhileStatement *while_statement) {
  auto if_cond_expression = Accept(while_statement->GetExpression());

  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  current_frame_->SetupScope();
  auto while_stmt = Accept(while_statement->GetStatement());
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  current_frame_->TearDownScope();

  IRT::Label label_cond;
  IRT::Label label_true;
  IRT::Label label_join;

  IRT::Statement *suffix = new IRT::LabelStatement(label_join);

  IRT::Label *result_true = &label_join;

  if (while_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
      new IRT::LabelStatement(label_true),
      new IRT::SeqStatement(
        while_stmt->ToStatement(), new IRT::SeqStatement(
          new IRT::JumpStatement(label_cond), suffix))
    );
  }

  tos_value_ = new IRT::StatementWrapper(
    new IRT::SeqStatement(new IRT::LabelStatement(label_cond), new IRT::SeqStatement(
      if_cond_expression->ToConditional(*result_true, label_join), suffix)
    )
  );
}
void IrtreeBuildVisitor::Visit(SimpleLvalue *simple_lvalue) {
  IRT::Expression *var_expression =
    current_frame_->GetAddress(simple_lvalue->GetIdentifier());
  tos_value_ = new IRT::ExpressionWrapper(var_expression);
}
void IrtreeBuildVisitor::Visit(ArrayElementLvalue *array_element_lvalue) {
  /// TODO
}
void IrtreeBuildVisitor::Visit(AccessToArrayElementExpression *access_to_array_element_expression) {
  /// TODO
}
void IrtreeBuildVisitor::Visit(ArrayNewExpression *array_new_expression) {
  /// TODO
}
void IrtreeBuildVisitor::Visit(ArrayLengthExpression *array_length_expression) {
  /// TODO
}
void IrtreeBuildVisitor::Visit(BinaryOperatorExpression *binary_operator_expression) {
  auto left = Accept(binary_operator_expression->GetFirst());
  auto right = Accept(binary_operator_expression->GetSecond());
  auto op = binary_operator_expression->GetBinaryOperator()->GetOperatorName();

  if (op == "&&") {
    tos_value_ = new IRT::AndConditionalWrapper(left, right);
  }
  if (op == "||") {
    tos_value_ = new IRT::OrConditionalWrapper(left, right);
  }
  if (op == "<") {
    tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::LT,
      left->ToExpression(),
      right->ToExpression()
    );
  }
  if (op == ">") {
    tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::GT,
      left->ToExpression(),
      right->ToExpression()
    );
  }
  if (op == "==") {
    tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::EQ,
      left->ToExpression(),
      right->ToExpression()
    );
  }
  if (op == "+") {
    tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
        IRT::BinaryOperatorType::PLUS,
        left->ToExpression(),
        right->ToExpression()
      )
    );
  }
  if (op == "-") {
    tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
        IRT::BinaryOperatorType::MINUS,
        left->ToExpression(),
        right->ToExpression()
      )
    );
  }
  if (op == "*") {
    tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
        IRT::BinaryOperatorType::MUL,
        left->ToExpression(),
        right->ToExpression()
      )
    );
  }
  if (op == "/") {
    tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
        IRT::BinaryOperatorType::DIV,
        left->ToExpression(),
        right->ToExpression()
      )
    );
  }
  if (op == "%") {
    tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
        IRT::BinaryOperatorType::MOD,
        left->ToExpression(),
        right->ToExpression()
      )
    );
  }
}

void IrtreeBuildVisitor::Visit(NewExpression *new_expression) {
  auto expr = CreateObject(new PrimitiveSimpleType(new SimpleType(new_expression->GetTypeIdentifier())));
  tos_value_ = new IRT::ExpressionWrapper(expr);
}
void IrtreeBuildVisitor::Visit(ExpressionList *expression_list) {
  /// do nothing (it is params in method invocation)
}
void IrtreeBuildVisitor::Visit(IdentExpression *ident_expression) {
  auto address = current_frame_->GetAddress(ident_expression->GetIdentifier());
  tos_value_ = new IRT::ExpressionWrapper(address);
}
void IrtreeBuildVisitor::Visit(MethodInvocationExpression *method_invocation_expression) {
  method_invocation_expression->GetMethodInvocation()->Accept(this);
}
void IrtreeBuildVisitor::Visit(NotExpression *not_expression) {
  auto wrapper = Accept(not_expression->GetExpression());
  tos_value_ = new IRT::NegateConditionalWrapper(wrapper);
}
void IrtreeBuildVisitor::Visit(NumberExpression *number_expression) {
  tos_value_ = new IRT::ExpressionWrapper(new IRT::ConstExpression(number_expression->GetValue()));
}
void IrtreeBuildVisitor::Visit(ParenthesisExpression *parenthesis_expression) {
  tos_value_ = Accept(parenthesis_expression->GetExpression());
}
void IrtreeBuildVisitor::Visit(ThisExpression *this_expression) {
  tos_value_ = new IRT::ExpressionWrapper(current_frame_->GetAddress("this"));
}
void IrtreeBuildVisitor::Visit(BoolExpression *bool_expression) {
  tos_value_ = new IRT::ExpressionWrapper(new IRT::ConstExpression(bool_expression->GetValue()));
}
void IrtreeBuildVisitor::Visit(Declaration *declaration) {
  if (declaration->IsVariable()) {
    declaration->GetVariableDeclaration()->Accept(this);
  } else {
    declaration->GetMethodDeclaration()->Accept(this);
  }
}
void IrtreeBuildVisitor::Visit(DeclarationList *declaration_list) {
  for (auto d : declaration_list->GetDeclarations()) {
    if (!d->IsVariable()) {
      while (!offsets_.empty()) {
        offsets_.pop();
      }
      d->GetMethodDeclaration()->Accept(this);
    }
  }
}
void IrtreeBuildVisitor::Visit(MethodDeclaration *method_declaration) {
  current_layer_ = tree_->GetScopeByName(Symbol(method_declaration->GetIdentifier()));
  offsets_.push(0);
  std::string method_name = current_class_name_ + "::" + method_declaration->GetIdentifier();

  current_frame_ = new IRT::FrameTranslator(method_name, current_class_name_);
  frame_translator_[method_name] = current_frame_;

  method_declaration->GetFormals()->Accept(this);
  current_frame_->AddReturnAddress();

  auto statements_ir = Accept(method_declaration->GetStatements());

  if (statements_ir) {
    tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(new IRT::LabelStatement(IRT::Label(method_name)),
                            statements_ir->ToStatement()));
  } else {
    throw std::runtime_error("Statements in method can't be empty");
    /*
    // generating return 0
    tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
        new IRT::LabelStatement(IRT::Label(function->name_)),
        new IRT::MoveStatement(
          current_frame_->GetReturnValueAddress()->ToExpression(),
          new IRT::ConstExpression(0)
        )
      )
    );
     */
  }
  method_trees_.emplace(method_name, tos_value_->ToStatement());
}
void IrtreeBuildVisitor::Visit(VariableDeclaration *variable_declaration) {
  tos_value_ = nullptr;
  if (variable_declaration->GetType()->IsSimpleType()) {
    current_frame_->AddLocalVariable(variable_declaration->GetIdentifier());
    auto id = variable_declaration->GetType()->GetSimpleType()->GetSimpleTypeIdentifier();
    if (id != "int" && id != "boolean" && id != "void") {
      auto expr = current_frame_->GetAddress(variable_declaration->GetIdentifier());
      IRT::Expression *value =
        CreateObject(new PrimitiveSimpleType(
          new SimpleType(variable_declaration->GetType()->GetSimpleType()->GetSimpleTypeIdentifier())));
      tos_value_ =
        new IRT::StatementWrapper(new IRT::MoveStatement(expr, value));
    }
  } else {
    /// TODO - add realization for arrays
  }
}

void IrtreeBuildVisitor::Visit(ClassDeclaration *class_declaration) {
  current_class_name_ = class_declaration->GetIdentifier();
  class_declaration->GetDeclarationList()->Accept(this);
}
void IrtreeBuildVisitor::Visit(ClassDeclarationList *class_declaration_list) {
  for (auto cl_decl : class_declaration_list->GetClassDeclarations()) {
    cl_decl->Accept(this);
  }
}
void IrtreeBuildVisitor::Visit(MainClass *main_class) {
  while (!offsets_.empty()) {
    offsets_.pop();
  }
  offsets_.push(0);
  current_layer_ = tree_->GetScopeByName(Symbol("main"));

  current_class_name_ = "main";
  std::string method_name = current_class_name_ + "::" + "main";

  current_frame_ = new IRT::FrameTranslator(method_name, current_class_name_);
  frame_translator_[method_name] = current_frame_;
  current_frame_->AddReturnAddress();

  auto statements_ir = Accept(main_class->GetStatementList());

  if (statements_ir) {
    tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(new IRT::LabelStatement(IRT::Label(method_name)),
                            statements_ir->ToStatement()));
  } else {
    throw std::runtime_error("Statements in method can't be empty");
    /*
    // generating return 0
    tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
        new IRT::LabelStatement(IRT::Label(function->name_)),
        new IRT::MoveStatement(
          current_frame_->GetReturnValueAddress()->ToExpression(),
          new IRT::ConstExpression(0)
        )
      )
    );
     */
  }
  method_trees_.emplace(method_name, tos_value_->ToStatement());
}
void IrtreeBuildVisitor::Visit(Type *type) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(TypeIdentifier *type_identifier) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(MethodInvocation *method_invocation) {
  auto *irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(Accept(method_invocation->GetExpression())->ToExpression());

  irt_expressions->Add(Accept(method_invocation->GetFirst())->ToExpression());
  for (auto it : method_invocation->GetExpressionList()->GetExpressions()) {
    irt_expressions->Add(Accept(it)->ToExpression());
  }
  std::string class_name = type_resolver_->Accept(method_invocation->GetExpression());
  tos_value_ = new IRT::ExpressionWrapper(new IRT::CallExpression(new IRT::NameExpression
                                                                    (IRT::Label(class_name + "::"
                                                                                  + method_invocation->GetIdentifier())),
                                                                  irt_expressions));
}

void IrtreeBuildVisitor::Visit(FormalList *formal_list) {
  current_frame_->AddArgumentAddress("this");
  for (auto param : formal_list->GetFormals()) {
    current_frame_->AddArgumentAddress(param->GetIdentifier());
  }
}
void IrtreeBuildVisitor::Visit(Formal *formal) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(BinaryOperator *binary_operator) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(Program *program) {
  program->GetClassDeclarationList()->Accept(this);
  program->GetMainClass()->Accept(this);
}
void IrtreeBuildVisitor::Visit(Expression *expression) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(Lvalue *lvalue) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(Statement *statement) {
  /// do nothing
}
void IrtreeBuildVisitor::Visit(LocalVariableDeclarationStatement *local_variable_declaration_statement) {
  local_variable_declaration_statement->GetLocalVariableDeclaration()->Accept(this);
}
void IrtreeBuildVisitor::SetTree(ScopeLayerTree *tree) {
  tree_ = tree;
}
ScopeLayer *IrtreeBuildVisitor::GetCurrentLayer() const {
  return current_layer_;
}
const std::string &IrtreeBuildVisitor::GetCurrentClassName() const {
  return current_class_name_;
}
IrtreeBuildVisitor::IrtreeBuildVisitor() : type_resolver_(new TypeResolver(this)) {
}