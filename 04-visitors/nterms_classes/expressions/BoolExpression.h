

#include "Expression.h"
class BoolExpression : public Expression {
public:
  explicit BoolExpression(bool value);
  void Accept(Visitor* visitor) override;
  bool GetValue() const;
  void SetValue(bool value);

private:
  bool value_;
};

