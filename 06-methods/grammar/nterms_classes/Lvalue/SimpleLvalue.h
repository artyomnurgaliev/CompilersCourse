#pragma once

#include <string>
#include "Lvalue.h"
class SimpleLvalue : public Lvalue {
public:
  bool IsSimple() override;
  explicit SimpleLvalue(std::string identifier);
  void Accept(Visitor* visitor) override;
  const std::string &GetIdentifier() const;
  void SetIdentifier(const std::string &identifier);

private:
  std::string identifier_;
};
