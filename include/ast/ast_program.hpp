#ifndef ast_program_hpp
#define ast_program_hpp

#define N_SPACE 2  // indentation in number of spaces

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Program;

typedef const Program *ProgramPtr;
typedef std::map<std::string, ProgramPtr> Binding;

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
// declaration    D
// return         R
// if else        I
// while          W
// function       F

class Program {
 protected:
  int node_type;

 public:
  virtual ~Program() {}
  virtual void print(std::ostream &dst, int indentation) const = 0;
  virtual int evaluate(Binding *binding) const = 0;
  int getType() const;
  void print_indent(std::ostream &dst, int &indentation) const;
};
#endif
