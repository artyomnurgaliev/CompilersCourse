#include <objects/objs/Object.h>
#include "TemplateVisitor.h"

#include "elements.h"

template<typename T>
T TemplateVisitor<T>::Accept(BaseElement * element) {
    element->Accept(this);
    return tos_value_;
}

template Object* TemplateVisitor<Object*>::Accept(BaseElement* element);