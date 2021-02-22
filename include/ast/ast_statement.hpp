#ifndef ast_statement_hpp
#define ast_statement_hpp

#include "ast_program.hpp"

class Statement : public Program {
 private:
  Program *expressions[];

 public:
  Statement() {}
};
#endif
