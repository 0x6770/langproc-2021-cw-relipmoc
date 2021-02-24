#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_program.hpp"
#include "ast_statement.hpp"

class Function : public Program {
 private:
  std::string *type;
  std::string *name;
  StatementList *statements;

 public:
  Function(std::string *_type, std::string *_name, StatementList *_statements)
      : type(_type), name(_name), statements(_statements) {
    fprintf(stderr, "construct Function\n");
    node_type = 'F';
  }
  virtual void print(std::ostream &dst) const override {
    dst << *type;
    dst << " ";
    dst << *name;
    dst << "() {\n";
    statements->print(dst);
    dst << "}";
  }
  virtual int evaluate() const override { return statements->evaluate(); }
};
#endif
