#ifndef ast_assignments_hpp
#define ast_assignments_hpp

#include "ast_operation.hpp"

////////////////////////////////////////
// Addition Equal
////////////////////////////////////////

class AddEqual : public Operation {
 public:
  AddEqual(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// subtraction equal
////////////////////////////////////////

class SubEqual : public Operation {
 public:
  SubEqual(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// product assignment
////////////////////////////////////////

class MulEqual : public Operation {
 public:
  MulEqual(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

class QuoEqual : public Operation {
 public:
  QuoEqual(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

class ModEqual : public Operation {
 public:
  ModEqual(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

class ShiftEqual_L : public Operation {
 public:
  ShiftEqual_L(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

class ShiftEqual_R : public Operation {
 public:
  ShiftEqual_R(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

class BitwiseEqual_AND : public Operation {
 public:
  BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

class BitwiseEqual_OR : public Operation {
 public:
  BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

class BitwiseEqual_XOR : public Operation {
 public:
  BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Suffix/postfix increment
////////////////////////////////////////
class Increment_Post : public Operation {
 public:
  Increment_Post(ProgramPtr _left, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Prefix increment
////////////////////////////////////////

class Increment_Pre : public Operation {
 public:
  Increment_Pre(ProgramPtr _left, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Suffix/postfix decrement
////////////////////////////////////////

class Decrement_Post : public Operation {
 public:
  Decrement_Post(ProgramPtr _left, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Prefix decrement
////////////////////////////////////////

class Decrement_Pre : public Operation {
 public:
  Decrement_Pre(ProgramPtr _left, int _pos);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

#endif
