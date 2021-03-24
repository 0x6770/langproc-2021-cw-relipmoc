#ifndef ast_pointer_hpp
#define ast_pointer_hpp

#include "ast_program.hpp"

class AddressOf : public Program {
 private:
  ProgramPtr left;

 public:
  AddressOf(ProgramPtr _expression, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

class Dereference : public Program {
 private:
  ProgramPtr left;
  int is_write;

 public:
  Dereference(ProgramPtr _expression, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  void read(int _read);
  std::string getVariableType() override;
};

#endif
