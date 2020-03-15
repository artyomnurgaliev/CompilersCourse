
#include <string>
#include "Lvalue.h"
class SimpleLvalue : public Lvalue {
public:
  explicit SimpleLvalue(std::string identifier);
private:
  std::string identifier_;
};
