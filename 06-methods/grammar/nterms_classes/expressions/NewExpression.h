#pragma once


#include "Expression.h"
#include <nterms_classes/TypeIdentifier.h>
class NewExpression : public Expression{
public:
  explicit NewExpression(TypeIdentifier* type_identifier);
  void Accept(Visitor* visitor) override;
  TypeIdentifier *GetTypeIdentifier() const;
  void SetTypeIdentifier(TypeIdentifier *type_identifier);

private:
  TypeIdentifier* type_identifier_;
};

