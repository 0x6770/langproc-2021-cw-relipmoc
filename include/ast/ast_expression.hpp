#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_program.hpp"

class Expression : public Program {
 private:
  int number;

 public:
  Expression(int _number) : number(_number) {
    printf("construct Expression\n");
  }
  virtual void print(std::ostream &dst) const override { dst << number; }
};
#endif
