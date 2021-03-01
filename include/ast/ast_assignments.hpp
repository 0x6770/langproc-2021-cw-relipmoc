#ifndef ast_assignments_hpp
#define ast_assignments_hpp

#include "ast_program.hpp"


////////////////////////////////////////
// Addition Equal
////////////////////////////////////////

class AddEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  AddEqual(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};


////////////////////////////////////////
// subtraction equal
////////////////////////////////////////

class SubEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  SubEqual(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};



////////////////////////////////////////
// product assignment
////////////////////////////////////////

class MulEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  MulEqual(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

class QuoEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  QuoEqual(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

class ModEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  ModEqual(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

class ShiftEqual_L : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  ShiftEqual_L(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

class ShiftEqual_R : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  ShiftEqual_R(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

class BitwiseEqual_AND : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

class BitwiseEqual_OR : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

class BitwiseEqual_XOR : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int pos;

 public:
  BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right,int _pos);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual int codeGen(Binding *binding,int reg) const override;
};

#endif