//
// Created by Pavel Akhtyamov on 24.03.2020.
//

#pragma once

#include "ObjectType.h"
#include <nterms_classes/type/Type.h>
#include <nterms_classes/type/SimpleType.h>
#include <nterms_classes/type/ArrayType.h>

class PrimitiveObjectType : public ObjectType {
public:
   std::string GetTypeName() override;
  explicit PrimitiveObjectType(Type* type);
private:
  Type* type_;

};



