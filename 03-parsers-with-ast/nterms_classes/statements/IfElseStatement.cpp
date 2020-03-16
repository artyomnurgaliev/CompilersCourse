
#include "IfElseStatement.h"
IfElseStatement::IfElseStatement(Expression *expression, Statement *statement,
                                 Statement *else_statement)
    : expression_(expression), statement_(statement),
      else_statement_(else_statement) {}
