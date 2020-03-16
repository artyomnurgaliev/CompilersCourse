//
// Created by artyom on 15.03.2020.
//

#include "MethodInvocation.h"

#include <utility>
MethodInvocation::MethodInvocation(Expression *expression,
                                   std::string identifier)
    : expression_(expression), identifier_(std::move(identifier)) {}
MethodInvocation::MethodInvocation(Expression *expression,
                                   std::string identifier, Expression *first,
                                   ExpressionList *expression_list)
    : expression_(expression), identifier_(std::move(identifier)),
      first_(first), expression_list_(expression_list) {}
