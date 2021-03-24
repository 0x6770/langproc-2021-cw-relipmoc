#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_program.hpp"

// TODO: new binding map<string name, int index>
////////////////////////////////////////
// Function
////////////////////////////////////////

class Function : public Program {
 private:
  std::string type;
  std::string name;
  Binding binding;  // for parameters
  ProgramPtr statements;
  ProgramPtr arguments;
  int with_param;
  int with_function_call = 0;
  int is_define = 0;
  int arg_size;

 public:
  Function(std::string _type, std::string _name, ProgramPtr _statements,
           int _pos, int _call, int _arg_size);
  Function(std::string _type, std::string _name, ProgramPtr _statements,
           ProgramPtr _arguments, int _pos, int _call, int _arg_size);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

////////////////////////////////////////
// Param -- single parameter
////////////////////////////////////////
class Param : public Program {
 private:
  std::string type;
  std::string name;
  int is_pointer;

 public:
  Param(std::string _type, std::string _name);
  Param(std::string _type, std::string _name, int _is_pointer);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  Binding return_bind(Binding &_binding, int pos);
  std::string getType();
  std::string getName();
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

////////////////////////////////////////
// parameter list
////////////////////////////////////////
class Paramlist : public Program {
 private:
  std::vector<ProgramPtr> parameters;

 public:
  Paramlist();
  Paramlist(ProgramPtr _argument);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  Binding return_bind(const Binding &_binding, int _pos);
  void add_argument(ProgramPtr _argument);
  std::string get_type_string();
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

////////////////////////////////////////
// A overall class which can contain global statements and multiple functions;
////////////////////////////////////////
class MultiFunction : public Program {
 private:
  std::vector<ProgramPtr> functions;

 public:
  MultiFunction(ProgramPtr _function);
  void add_function(ProgramPtr _function);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

////////////////////////////////////////
// function call class
////////////////////////////////////////

// functioncall should be similar to the expression
class FunctionCall : public Program {
 private:
  std::string name;
  ProgramPtr arguments;
  int with_argument = 0;

 public:
  // function calls without arguments:
  FunctionCall(std::string _name, int _pos);
  FunctionCall(std::string _name, ProgramPtr _argument, int _pos);
  void add_argument(ProgramPtr _argument);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

////////////////////////////////////////
// Expression List
////////////////////////////////////////
class ExpressionList : public Program {
 private:
  std::vector<ProgramPtr> arguments;

 public:
  ExpressionList(ProgramPtr _argument);
  void add_argument_expression(ProgramPtr _expr);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

// Function definition:

class FunctionDeclare : public Program {
 private:
  ProgramPtr parameters;
  std::string name;

 public:
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  FunctionDeclare(std::string _name, ProgramPtr _param_list);
  virtual void passFunctionName(std::string _name, int _pos) override;
  FunctionDeclare(std::string _name);
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

#endif
