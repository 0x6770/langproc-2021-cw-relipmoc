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
  Binding return_bind(Binding &_binding,int pos);
  std::string getType();
};

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
};

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

};

// functioncall should be similar to the expression
class FunctionCall : public Program{
private:
   std::string name;
   std::vector<ProgramPtr> arguments;
public: 
  // function calls without arguments:
  FunctionCall(std::string _name);
  void add_Arguments(ProgramPtr _Argument); 
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
 
};

#endif
