#ifndef ast_op_bitwise_hpp
#define ast_op_bitwise_hpp

#include "ast_operation.hpp"

////////////////////////////////////////
// BitwiseAnd
////////////////////////////////////////

class BitwiseAnd : public Operation {
 public:
  BitwiseAnd(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// BitwiseOr
////////////////////////////////////////

class BitwiseOr : public Operation {
 public:
  BitwiseOr(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// ShiftLeft
////////////////////////////////////////

class ShiftLeft : public Operation {
 public:
  ShiftLeft(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// ShiftRight
////////////////////////////////////////

class ShiftRight : public Operation {
 public:
  ShiftRight(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// BitwiseXor
////////////////////////////////////////

class BitwiseXor : public Operation {
 public:
  BitwiseXor(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

#endif
