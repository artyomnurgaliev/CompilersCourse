#pragma once
#include "ObjectType.h"
#include <nterms_classes/type/Type.h>
#include <string>
#include <vector>

class MainClassType : public ObjectType {
public:
  MainClassType(StatementList* statement_list);
  std::string GetTypeName() override;
private:
  StatementList* statement_list_;
};