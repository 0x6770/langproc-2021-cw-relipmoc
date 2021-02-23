#ifndef ast_statement_hpp
#define ast_statement_hpp

#include "ast_program.hpp"

class Statement : public Program {
 private:
  ProgramPtr expression;

 public:
  Statement(ProgramPtr _expression) : expression(_expression) {
    printf("construct Statement\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "return ";
    expression->print(dst);
  }
};
#endif
