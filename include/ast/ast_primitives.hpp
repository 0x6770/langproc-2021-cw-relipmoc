#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include "ast_program.hpp"

class Type : public Program {
 private:
  c_type type;

 public:
  Type(c_type _type) : type(_type) { fprintf(stderr, "construct Type\n"); }
  virtual void print(std::ostream &dst) const override {
    switch (type) {
      case c_type::c_int:
        dst << "int ";
        break;
      default:
        dst << "error";
        exit(1);
    }
  }
  virtual int evaluate() const override { exit(1); }
};

#endif
