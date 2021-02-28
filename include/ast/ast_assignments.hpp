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

 public:
  AddEqual(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};


////////////////////////////////////////
// subtraction equal
////////////////////////////////////////

class SubEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  SubEqual(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};



////////////////////////////////////////
// product assignment
////////////////////////////////////////

class MulEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  MulEqual(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

class QuoEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  QuoEqual(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

class ModEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  ModEqual(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

class ShiftEqual_L : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  ShiftEqual_L(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

class ShiftEqual_R : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  ShiftEqual_R(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

class BitwiseEqual_AND : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

class BitwiseEqual_OR : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

class BitwiseEqual_XOR : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif