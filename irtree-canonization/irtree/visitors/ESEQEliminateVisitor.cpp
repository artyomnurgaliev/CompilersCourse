
#include <unordered_set>
#include "ESEQEliminateVisitor.h"

#include "BaseElements.h"

namespace IRT {

void ESEQEliminateVisitor::Visit(ExpStatement *stmt) {
  IrtStorage elements = Accept(stmt->GetExpression());
  if (elements.expression_->IsESEQ()) {
    tos_value_.statement_ = ((EseqExpression *) elements.expression_)->statement_;
  } else {
    tos_value_.statement_ = new ExpStatement(elements.expression_);
  }
}
void ESEQEliminateVisitor::Visit(ConstExpression *const_expression) {
  tos_value_.expression_ = new ConstExpression(const_expression->Value());
}
void ESEQEliminateVisitor::Visit(JumpConditionalStatement *jump_conditional_statement) {
  auto op = jump_conditional_statement->operator_type_;
  auto lhs = Accept(jump_conditional_statement->left_operand_).expression_;
  auto rhs = Accept(jump_conditional_statement->right_operand_).expression_;
  auto l1 = jump_conditional_statement->label_true_;
  auto l2 = jump_conditional_statement->label_false_;
  if (lhs->IsESEQ() && rhs->IsESEQ()) {
    auto eseq1 = (EseqExpression *) lhs;
    auto eseq2 = (EseqExpression *) rhs;
    if (IsCommute(eseq2->statement_, lhs)) {
      tos_value_.statement_ = new SeqStatement(
        eseq1->statement_, new SeqStatement(eseq2->statement_,
                                            new JumpConditionalStatement(op,
                                                                         eseq1->expression_,
                                                                         eseq2->expression_,
                                                                         l1,
                                                                         l2))
      );
    } else {
      Temporary t;
      tos_value_.statement_ = new SeqStatement(
        eseq1->statement_, new SeqStatement(
          new MoveStatement(new TempExpression(t), eseq1->expression_),
          new SeqStatement(eseq2->statement_, new JumpConditionalStatement(
            op, new TempExpression(t), eseq2->expression_, l1, l2))));
    }
  } else if (lhs->IsESEQ()) {
    auto eseq = (EseqExpression *) lhs;
    tos_value_.statement_ = new SeqStatement(eseq->statement_,
                                             new JumpConditionalStatement(op, eseq->expression_, rhs, l1, l2));

  } else if (rhs->IsESEQ()) {
    auto eseq = (EseqExpression *) rhs;
    if (IsCommute(eseq->statement_, lhs)) {
      tos_value_.statement_ = new SeqStatement(eseq->statement_,
                                               new JumpConditionalStatement(op, lhs, eseq->expression_, l1, l2));
    } else {
      Temporary t;
      tos_value_.statement_ = new SeqStatement(
        new MoveStatement(new TempExpression(t), lhs),
        new SeqStatement(eseq->statement_, new JumpConditionalStatement(
          op, new TempExpression(t), eseq->expression_, l1, l2)));
    }
  } else {
    tos_value_.statement_ = new JumpConditionalStatement(
      op, lhs, rhs, l1, l2
    );
  }
}
void ESEQEliminateVisitor::Visit(MoveStatement *move_statement) {
  auto source = Accept(move_statement->source_).expression_;
  auto target = Accept(move_statement->target_).expression_;
  if (source->IsESEQ() && target->IsESEQ()) {
    auto eseq1 = (EseqExpression *) source;
    auto eseq2 = (EseqExpression *) target;
    tos_value_.statement_ = new SeqStatement(eseq1->statement_,
                                             new SeqStatement(eseq2->statement_, new MoveStatement(eseq1->expression_,
                                                                                                   eseq2->expression_)));
  } else if (source->IsESEQ()) {
    auto eseq = (EseqExpression *) source;
    tos_value_.statement_ =
      new SeqStatement(eseq->statement_,
                       new MoveStatement(eseq->expression_, target));
  } else if (target->IsESEQ()) {
    auto eseq = (EseqExpression *) target;
    tos_value_.statement_ =
      new SeqStatement(eseq->statement_,
                       new MoveStatement(source, eseq->expression_));
  } else {
    tos_value_.statement_ = new MoveStatement(source, target);
  }
}
void ESEQEliminateVisitor::Visit(SeqStatement *seq_statement) {
  auto first = Accept(seq_statement->first_statement_).statement_;
  auto second = Accept(seq_statement->second_statement_).statement_;

  tos_value_.statement_ = new SeqStatement(
    first,
    second
  );
}
void ESEQEliminateVisitor::Visit(LabelStatement *label_statement) {
  tos_value_.statement_ = new LabelStatement(label_statement->label_);
}
void ESEQEliminateVisitor::Visit(BinopExpression *binop_statement) {
  auto op = binop_statement->operator_type_;
  auto lhs = Accept(binop_statement->first_).expression_;
  auto rhs = Accept(binop_statement->second_).expression_;
  if (lhs->IsESEQ() && rhs->IsESEQ()) {
    auto eseq1 = (EseqExpression *) lhs;
    auto eseq2 = (EseqExpression *) rhs;
    if (IsCommute(eseq2->statement_, lhs)) {
      tos_value_.expression_ = new EseqExpression(eseq1->statement_,
                                                  new EseqExpression(eseq2->statement_,
                                                                     new BinopExpression(op,
                                                                                         eseq1->expression_,
                                                                                         eseq2->expression_)
                                                  ));
    } else {
      Temporary t;
      tos_value_.expression_ = new EseqExpression(eseq1->statement_, new EseqExpression(
        new MoveStatement(new TempExpression(t), eseq1->expression_),
        new EseqExpression(eseq2->statement_,
                           new BinopExpression(op, new TempExpression(t), eseq2->expression_))
      ));
    }
  } else if (lhs->IsESEQ()) {
    auto eseq = (EseqExpression *) lhs;
    tos_value_.expression_ = new EseqExpression(eseq->statement_,
                                                new BinopExpression(op, eseq->expression_, rhs));
  } else if (rhs->IsESEQ()) {
    auto eseq = (EseqExpression *) rhs;
    if (IsCommute(eseq->statement_, lhs)) {
      tos_value_.expression_ = new EseqExpression(
        eseq->statement_, new BinopExpression(op, lhs, eseq->expression_));
    } else {
      Temporary t;
      tos_value_.expression_ = new EseqExpression(
        new MoveStatement(new TempExpression(t), lhs),
        new EseqExpression(eseq->statement_,
                           new BinopExpression(op, new TempExpression(t), eseq->expression_))
      );
    }
  } else {
    tos_value_.expression_ = new BinopExpression(op, lhs, rhs);
  }
}
void ESEQEliminateVisitor::Visit(TempExpression *temp_expression) {
  tos_value_.expression_ = new TempExpression(temp_expression->temporary_);
}
void ESEQEliminateVisitor::Visit(MemExpression *mem_expression) {
  auto expr = Accept(mem_expression->expression_).expression_;
  if (expr->IsESEQ()) {
    auto eseq = (EseqExpression *) expr;
    tos_value_.expression_ = new EseqExpression(eseq->statement_,
                                                new MemExpression(eseq->expression_));
  } else {
    tos_value_.expression_ = new MemExpression(expr);
  }
}
void ESEQEliminateVisitor::Visit(JumpStatement *jump_statement) {
  tos_value_.statement_ = new JumpStatement(jump_statement->label_);
}
void ESEQEliminateVisitor::Visit(CallExpression *call_expression) {
  auto expression_list = Accept(call_expression->args_).expression_list_;
  auto func = Accept(call_expression->function_name_).expression_;

  ssize_t eseq_idx = -1;
  for (size_t i = 0; i < expression_list->expressions_.size(); ++i) {
    if (expression_list->expressions_[i]->IsESEQ()) {
      eseq_idx = i;
      break;
    }
  }

  if (eseq_idx == -1) {
    if (call_expression->function_name_->IsESEQ()) {
      auto func_eseq = (EseqExpression *) func;
      tos_value_.expression_ = new EseqExpression(func_eseq->statement_,
                                                  new CallExpression(func_eseq->expression_, expression_list));
    } else {
      tos_value_.expression_ = new CallExpression(func, expression_list);
    }
    return;
  } else {
    auto eseq = (EseqExpression *) (expression_list->expressions_[eseq_idx]);
    std::vector<Temporary> temporaries;
    std::unordered_set<size_t> noncommute_indexes;
    for (int i = 0; i < eseq_idx - 1; ++i) {
      if (!IsCommute(eseq->statement_, expression_list->expressions_[i])) {
        noncommute_indexes.insert(i);
      }
    }
    auto temporary_statements = eseq->statement_;
    for (size_t i = 0; i < noncommute_indexes.size(); ++i) {
      temporaries.emplace_back();
    }
    int size = temporaries.size() - 1;
    for (int i = eseq_idx; i >= 0; --i) {
      if (noncommute_indexes.find(i) != noncommute_indexes.end()) {
        temporary_statements = new SeqStatement(new MoveStatement(new TempExpression(temporaries[size--]),
                                                                  expression_list->expressions_[i]),
                                                temporary_statements);
      }
    }
    size = 0;
    auto expression_list_with_temporaries = new ExpressionList();
    for (size_t i = 0; i < expression_list->expressions_.size(); ++i) {
      if (i == eseq_idx) {
        expression_list_with_temporaries->Add(eseq->expression_);
      } else {
        if (noncommute_indexes.find(i) != noncommute_indexes.end()) {
          expression_list_with_temporaries->Add(new TempExpression(temporaries[size++]));
        } else {
          expression_list_with_temporaries->Add(expression_list->expressions_[i]);
        }
      }
    }
    if (call_expression->function_name_->IsESEQ()) {
      auto func_eseq = (EseqExpression *) func;
      tos_value_.expression_ = new EseqExpression(func_eseq->statement_, new EseqExpression(
        temporary_statements, new CallExpression(func_eseq->expression_, expression_list_with_temporaries)));
    } else {
      tos_value_.expression_ = new EseqExpression(
        temporary_statements, new CallExpression(func, expression_list_with_temporaries));
    }
  }

}
void ESEQEliminateVisitor::Visit(ExpressionList *expression_list) {
  auto expression_list_ = new ExpressionList();

  for (auto expression: expression_list->expressions_) {
    expression_list_->Add(Accept(expression).expression_);
  }
  tos_value_.expression_list_ = expression_list_;
}
void ESEQEliminateVisitor::Visit(NameExpression *name_expression) {
  tos_value_.expression_ = new NameExpression(name_expression->label_);
}
void ESEQEliminateVisitor::Visit(EseqExpression *eseq_expression) {
  auto stmt = Accept(eseq_expression->statement_).statement_;
  auto expr = Accept(eseq_expression->expression_).expression_;

  if (expr->IsESEQ()) {
    auto eseq = (EseqExpression *) expr;
    tos_value_.expression_ = new EseqExpression(new SeqStatement(
      stmt, eseq->statement_
    ), eseq->expression_);
  } else {
    tos_value_.expression_ = new EseqExpression(stmt, expr);
  }
}
Statement *ESEQEliminateVisitor::GetTree() {
  return tos_value_.statement_;
}
bool ESEQEliminateVisitor::IsCommute(IRT::Statement *s, IRT::Expression *e1) {
  if (s->IsExp()) {
    if (((ExpStatement *) s)->GetExpression()->IsCONST()) {
      return true;
    }
  }
  return e1->IsCONST() || e1->IsNAME();
}

}