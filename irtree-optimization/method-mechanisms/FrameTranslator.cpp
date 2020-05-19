//
// Created by akhtyamovpavel on 4/14/20.
//

#include <method-mechanisms/address/AddressInRegister.h>
#include <method-mechanisms/address/AddressInFrame.h>
#include <irtree/types/BinaryOperatorType.h>
#include "FrameTranslator.h"
#include "ClassStorage.h"
#include <irtree/nodes/expressions/ConstExpression.h>
#include <irtree/nodes/expressions/BinopExpression.h>
#include <irtree/nodes/expressions/MemExpression.h>
#include <iostream>

namespace IRT {
FrameTranslator::FrameTranslator(const std::string &function_name, const std::string &class_name)
  : function_name_(function_name), class_name_(class_name) {

  addresses_[frame_pointer_address_].push(new AddressInRegister(
    Temporary(frame_pointer_address_)
  ));

  addresses_[return_value_address_].push(new AddressInRegister(
    Temporary(return_value_address_)
  ));
}
void FrameTranslator::SetupScope() {
  symbols_.push("{");
}

void FrameTranslator::TearDownScope() {
  while (symbols_.top() != "{") {
    std::string symbol = symbols_.top();

//    std::cerr << "Popping " << symbol.GetName() << std::endl;

    addresses_[symbol].pop();
    if (addresses_[symbol].empty()) {
      addresses_.erase(symbol);
    }
    symbols_.pop();
  }
  symbols_.pop();
}

void FrameTranslator::AddLocalVariable(const std::string &name) {
  AddVariable(name);
}

Address *FrameTranslator::FramePointer() {
  return addresses_[frame_pointer_address_].top();
}

int FrameTranslator::GetOffset() {
  int tmp = max_offset_;
  max_offset_ += word_size_;
  return tmp;
}
void FrameTranslator::AddArgumentAddress(const std::string &name) {
  AddVariable(name);
}

void FrameTranslator::AddVariable(const std::string &name) {
  symbols_.push(name);

  if (addresses_.find(name) == addresses_.end()) {
    addresses_[name];
  }
  addresses_[name].push(
    new AddressInFrame(FramePointer(), GetOffset())
  );
}

Expression *FrameTranslator::GetField(const std::string &name) {
  IRT::Expression *this_ptr = addresses_["this"].top()->ToExpression();
  IRT::Expression *field_ptr;

  auto fields = ClassStorage::GetInstance().GetFields(Symbol(class_name_));
  bool is_found = false;
  size_t offset = 0;

  //// TODO - Attention - поля не в том порядке, в котором они должны быть,
  //// а в том, в котором хранятся в мапе, надо исправить
  for (const auto& field: fields) {
    std::cout << field.first.GetName() << std::endl;
  }

  for (const auto& field: fields) {
    if (field.first.GetName() == name) {
      is_found = true;
      break;
    }
    offset += field.second->GetSize();
  }
  if (is_found) {
    field_ptr = new MemExpression(
      new BinopExpression(BinaryOperatorType::PLUS,
                               this_ptr,
                               new ConstExpression(offset)));
  } else {
    throw std::runtime_error("Field doesn't exist");
  }
  return field_ptr;
}

IRT::Expression *FrameTranslator::GetAddress(const std::string &name) {
  if (addresses_[name].empty()) {
    return GetField(name);
  }
  return addresses_[name].top()->ToExpression();
}
void FrameTranslator::AddReturnAddress() {
  AddVariable(return_address_);
}

IRT::Expression *FrameTranslator::GetReturnValueAddress() {
  return GetAddress(return_value_address_);
}

}