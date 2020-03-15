#include "TemplateVisitor.h"

#include "symbol_table/Table.h"
#include <map>

#include "symbol_table/ScopeLayerTree.h"


class Interpreter : public TemplateVisitor<int> {
 public:
    Interpreter();
    void Visit(NumberExpression* expression) override;
    void Visit(BinaryOperatorExpression * expression) override;
    void Visit(SubstractExpression* expression) override;
    void Visit(MulExpression* expression) override;
    void Visit(DivExpression* expression) override;
    void Visit(IdentExpression* expression) override;
    void Visit(Assignment* assignment) override;
    void Visit(VarDecl* var_decl) override;
    void Visit(PrintStatement* statement) override;
    void Visit(AssignmentList* assignment_list) override;
    void Visit(ScopeAssignmentList* list) override;
    void Visit(Program* program) override;

    int GetResult(Program* program);

 private:
   //  Table table_;
    ScopeLayerTree tree_;
    std::shared_ptr<ScopeLayer> current_layer_;
    
};