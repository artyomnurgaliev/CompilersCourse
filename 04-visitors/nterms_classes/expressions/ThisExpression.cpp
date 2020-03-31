//
// Created by artyom on 15.03.2020.
//

#include "ThisExpression.h"
ThisExpression::ThisExpression() {}
void ThisExpression::Accept(Visitor *visitor) { visitor->Visit(this); }
