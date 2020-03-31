#pragma once


#include "Expression.h"
#include <nterms_classes/TypeIdentifier.h>
class DefenitionExpression : public Expression{
public:
  explicit DefenitionExpression(TypeIdentifier* type_identifier);
  void Accept(Visitor* visitor) override;
  TypeIdentifier *GetTypeIdentifier() const;
  void SetTypeIdentifier(TypeIdentifier *type_identifier);

private:
  TypeIdentifier* type_identifier_;
};

