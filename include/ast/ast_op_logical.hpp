#ifndef ast_op_logical_hpp
#define ast_op_logical_hpp

#include "ast_operation.hpp"

////////////////////////////////////////
// LessEqual
////////////////////////////////////////

class LessEqual : public Operation {
 private:
  int is_equal;

 public:
  LessEqual(ProgramPtr _left, ProgramPtr _right, int _pos, int _is_equal);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// GreaterEqual
////////////////////////////////////////

class GreaterEqual : public Operation {
 private:
  int is_equal;

 public:
  GreaterEqual(ProgramPtr _left, ProgramPtr _right, int _pos, int _is_equal);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Equal
////////////////////////////////////////

class Equal : public Operation {
 private:
  int is_equal;

 public:
  Equal(ProgramPtr _left, ProgramPtr _right, int _pos, int _is_equal);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// LogicalAnd
////////////////////////////////////////

class LogicalAnd : public Operation {
 public:
  LogicalAnd(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// LogicalOr
////////////////////////////////////////

class LogicalOr : public Operation {
 public:
  LogicalOr(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

#endif
