

#include "MainClassType.h"
MainClassType::MainClassType(StatementList *statement_list): statement_list_(statement_list) {
}
std::string MainClassType::GetTypeName() {
  return "MainClass";
}
