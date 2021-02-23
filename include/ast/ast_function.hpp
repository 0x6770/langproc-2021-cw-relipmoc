#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_program.hpp"

class Function : public Program {
 private:
  ProgramPtr type;
  std::string *name;
  ProgramPtr statement;

 public:
  Function(ProgramPtr _type, std::string *_name, ProgramPtr _statement)
      : type(_type), name(_name), statement(_statement) {
    printf("construct Function\n");
  }
  virtual void print(std::ostream &dst) const override {
    type->print(dst);
    dst << *name;
    dst << "() {";
    statement->print(dst);
    dst << "}";
  }
};
#endif
