#pragma once

#include <irtree/generators/Temporary.h>
#include <irtree/nodes/ExpressionList.h>
#include <irtree/nodes/expressions/CallExpression.h>
#include <irtree/nodes/expressions/ConstExpression.h>
#include <irtree/nodes/expressions/EseqExpression.h>
#include <irtree/nodes/expressions/NameExpression.h>
#include <irtree/nodes/expressions/TempExpression.h>
#include <irtree/nodes/expressions/BinopExpression.h>
#include <irtree/nodes/expressions/MemExpression.h>
#include <irtree/nodes/statements/SeqStatement.h>
#include <irtree/nodes/statements/MoveStatement.h>
#include <irtree/types/BinaryOperatorType.h>
#include <objects/PrimitiveSimpleType.h>

IRT::Expression *CreateObject(PrimitiveSimpleType *type) {
  auto *irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(new IRT::ConstExpression(type->GetSize()));

  IRT::Temporary result;
  return new IRT::EseqExpression(
    new IRT::MoveStatement(new IRT::TempExpression(result), new IRT::CallExpression(
      new IRT::NameExpression(IRT::Label("malloc")), irt_expressions)),
    new IRT::TempExpression(result)
  );
}
