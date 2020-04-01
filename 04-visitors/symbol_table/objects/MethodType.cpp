
#include "MethodType.h"
#include <nterms_classes/FormalList.h>

MethodType::MethodType(Type *type, FormalList *formal_list) : return_value_type_(type), formal_list_(formal_list){
}
