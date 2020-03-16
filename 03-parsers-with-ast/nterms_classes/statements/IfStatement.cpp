//
// Created by artyom on 15.03.2020.
//

#include "IfStatement.h"
IfStatement::IfStatement(Expression *expression, Statement *statement)
    : expression_(expression), statement_(statement) {}
