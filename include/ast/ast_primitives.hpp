#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include "ast_program.hpp"

class Type : public Program {
 private:
  c_type type;

 public:
  Type(c_type _type) : type(_type) { printf("construct Type\n"); }
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
};

class Integer : public Program {
 private:
  int value;

 public:
  Integer(int _value) : value(_value) { printf("construct Integer\n"); }
  virtual void print(std::ostream &dst) const override { dst << value; }
};

#endif
