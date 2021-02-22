#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_program.hpp"

class Function : public Program {
 private:
  Program *statements[];

 public:
  Function() {}
};
#endif
