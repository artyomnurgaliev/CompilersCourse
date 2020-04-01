//
// Created by Pavel Akhtyamov on 24.03.2020.
//

#pragma once

#include "ObjectType.h"
#include <nterms_classes/type/Type.h>

class PrimitiveObjectType : public ObjectType {
public:
  explicit PrimitiveObjectType(Type* type);
private:
  Type* type_;

};



