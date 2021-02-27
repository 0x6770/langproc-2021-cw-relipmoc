#ifndef ast_op_logical_hpp
#define ast_op_logical_hpp

#include "ast_program.hpp"

////////////////////////////////////////
// ShiftLeft
////////////////////////////////////////

class ShiftLeft : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  ShiftLeft(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// ShiftRight
////////////////////////////////////////

class ShiftRight : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  ShiftRight(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// LessEqual
////////////////////////////////////////

class LessEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int is_equal;

 public:
  LessEqual(ProgramPtr _left, ProgramPtr _right, int _is_equal);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// GreaterEqual
////////////////////////////////////////

class GreaterEqual : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int is_equal;

 public:
  GreaterEqual(ProgramPtr _left, ProgramPtr _right, int _is_equal);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Equal
////////////////////////////////////////

class Equal : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int is_equal;

 public:
  Equal(ProgramPtr _left, ProgramPtr _right, int _is_equal);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// LogicalAnd
////////////////////////////////////////

class LogicalAnd : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  LogicalAnd(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// LogicalOr
////////////////////////////////////////

class LogicalOr : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  LogicalOr(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif
