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
  Operation(ProgramPtr _left, ProgramPtr _right, int _pos);
  virtual int codeGen(const Binding &_binding, int reg) const override;
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
};

#endif
