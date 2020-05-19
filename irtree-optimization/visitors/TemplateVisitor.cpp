#include <irtree/tree_wrapper/SubtreeWrapper.h>
#include <objects/objs/Object.h>
#include "TemplateVisitor.h"
#include "elements.h"

template<typename T>
T TemplateVisitor<T>::Accept(BaseElement * element) {
    element->Accept(this);
    return tos_value_;
}

template Object* TemplateVisitor<Object*>::Accept(BaseElement* element);
template IRT::SubtreeWrapper* TemplateVisitor<IRT::SubtreeWrapper*>::Accept(BaseElement *element);
template std::string TemplateVisitor<std::string>::Accept(BaseElement *element);