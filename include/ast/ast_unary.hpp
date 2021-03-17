#ifndef ast_unary_hpp
#define ast_unary_hpp

#include "ast_program.hpp"

class SizeOf : public Program{
private: 
  ProgramPtr expression;
  std::string const_type;
  int is_type;
public:
  SizeOf(ProgramPtr _expression);
  SizeOf(std::string  _type);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual void bind(const Binding &_binding) override;
};

#endif