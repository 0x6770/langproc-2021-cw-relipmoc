#ifndef ast_op_bitwise_hpp
#define ast_op_bitwise_hpp

#include "ast_program.hpp"

////////////////////////////////////////
// BitwiseAnd
////////////////////////////////////////

class BitwiseAnd : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  BitwiseAnd(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// BitwiseOr
////////////////////////////////////////

class BitwiseOr : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  BitwiseOr(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif
