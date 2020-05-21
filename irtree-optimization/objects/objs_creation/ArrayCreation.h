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
#include <irtree/consts.h>
#include <objects/PrimitiveSimpleType.h>

IRT::Expression *CreateArray(IRT::Expression *array_size) {
  auto *irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(new IRT::BinopExpression(
    IRT::BinaryOperatorType::MUL,
    new IRT::ConstExpression(WORD_SIZE),
    new IRT::BinopExpression(IRT::BinaryOperatorType::PLUS, array_size, new IRT::ConstExpression(1)
    ))); // 1 byte - to store length of the array

  IRT::Temporary tmp;
  return new IRT::EseqExpression(
    new IRT::SeqStatement(new IRT::MoveStatement(new IRT::TempExpression(tmp),
                             new IRT::CallExpression(
                               new IRT::NameExpression(IRT::Label("malloc")),
                               irt_expressions)),
      // store length of the array
      new IRT::MoveStatement(new IRT::MemExpression(new IRT::TempExpression(tmp)), array_size)
    ),
    new IRT::TempExpression(tmp)
  );
}