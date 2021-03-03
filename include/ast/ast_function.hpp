#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_program.hpp"

// TODO: new binding map<string name, int index>

class Function : public Program {
 private:
  std::string type;
  std::string name;
  Binding binding;  // for parameters
  ProgramPtr statements;

 public:
  Function(std::string _type, std::string _name, ProgramPtr _statements,
           int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
};

class Param : public Program {
 private:
  std::string type;
  std::string name;

 public:
  Param(std::string _type, std::string _name);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
};

#endif
