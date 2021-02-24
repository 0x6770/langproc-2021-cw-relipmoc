#ifndef ast_program_hpp
#define ast_program_hpp

#include <iostream>
#include <string>
#include <vector>

class Program;

typedef const Program *ProgramPtr;

// node_type
//
// +              a
// -              s
// *              t
// /              d
// %              m
// ^              p
//
// integer        i
// char           c
// number         n
//
// expr           E
// statement      S
// statement_list L
// assignment     A
// return         R
// if else        I
// while          W
// function       F

class Program {
 protected:
  int node_type;

 public:
  virtual ~Program() {}
  virtual void print(std::ostream &dst) const = 0;
  virtual int evaluate() const = 0;
  int getType() const { return node_type; };
};
#endif
