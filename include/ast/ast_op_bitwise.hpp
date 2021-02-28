#ifndef ast_op_bitwise_hpp
#define ast_op_bitwise_hpp

#include "ast_operation.hpp"

////////////////////////////////////////
// BitwiseAnd
////////////////////////////////////////

class BitwiseAnd : public Operation {
 public:
  BitwiseAnd(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// BitwiseOr
////////////////////////////////////////

class BitwiseOr : public Operation {
 public:
  BitwiseOr(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// ShiftLeft
////////////////////////////////////////

class ShiftLeft : public Operation {
 public:
  ShiftLeft(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// ShiftRight
////////////////////////////////////////

class ShiftRight : public Operation {
 public:
  ShiftRight(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

#endif
