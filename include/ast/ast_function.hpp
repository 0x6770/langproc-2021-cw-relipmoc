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
  ProgramPtr Arguments;
  int with_param;

 public:
  Function(std::string _type, std::string _name, ProgramPtr _statements,
           int _pos);
  Function(std::string _type, std::string _name, ProgramPtr _statements, ProgramPtr _Arguments,
           int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name) override;
};


////////////////////////////////////////
// Param -- single parameter
////////////////////////////////////////
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
  Binding return_bind(Binding &_binding,int pos);
  std::string getType();
  virtual void passFunctionName(std::string _name) override;
};


////////////////////////////////////////
// parameter list
////////////////////////////////////////
class Paramlist : public Program {
 private:
  std::vector<ProgramPtr> parameters;

 public:
  Paramlist();
  Paramlist(ProgramPtr argument);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  Binding return_bind(const Binding &_binding,int pos);
  void add_argument(ProgramPtr argument);
  std::string get_type_string();
  virtual void passFunctionName(std::string _name) override;
};


////////////////////////////////////////
// A overall class which can contain global statements and multiple functions;
////////////////////////////////////////
class MultiFunction : public Program {
private:
  std::vector<ProgramPtr> functoins;
public:
  MultiFunction(ProgramPtr _funciton);
  void add_function(ProgramPtr _function);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name) override;

};

////////////////////////////////////////
// function call class
////////////////////////////////////////

// functioncall should be similar to the expression
class FunctionCall : public Program{
private:
   std::string name;
   ProgramPtr expression_list;
public: 
  // function calls without arguments:
  FunctionCall(std::string _name, ProgramPtr _argument);
  void add_Arguments(ProgramPtr _Argument); 
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name) override;
};

////////////////////////////////////////
// Expression List
////////////////////////////////////////
class ExpressionList : public Program{
private: 
  std::vector<ProgramPtr> arguments;
public:
  ExpressionList(ProgramPtr _argument);
  void add_argument_expression(ProgramPtr _expr);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name) override;
};


#endif
