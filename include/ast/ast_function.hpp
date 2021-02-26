#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_program.hpp"

class Function : public Program {
 private:
  std::string *type;
  std::string *name;
  ProgramPtr statements;

 public:
  Function(std::string *_type, std::string *_name, ProgramPtr _statements);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};
#endif
