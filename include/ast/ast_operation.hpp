#ifndef ast_operation_hpp
#define ast_operation_hpp

#include "ast_program.hpp"

////////////////////////////////////////
// Operation
////////////////////////////////////////

class Operation : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Operation(ProgramPtr _left, ProgramPtr _right, int pos);
  virtual int codeGen(Binding *binding, int reg) const override;
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif
