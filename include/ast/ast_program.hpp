#ifndef ast_program_hpp
#define ast_program_hpp

#define N_SPACE 2  // indentation in number of spaces

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Program;

typedef const Program *ProgramPtr;
typedef std::map<std::string, int> Binding;  // map<string name, int pos>

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
  int size;
  int pos;          // position of a variable or expression in stack frame
  Binding binding;  // variables binding

 public:
  virtual ~Program() {}
  virtual void print(std::ostream &dst, int indentation) const = 0;
  virtual int evaluate(const Binding &_binding) const = 0;
  // Print mips assembly code.
  // Binding *binding contains information about every variable in current
  // scope and above.
  // int reg is the index of registor to store result.
  // return its position in stack frame if it is a variable, else return 0.
  virtual int codeGen(const Binding &_binding, int reg) const = 0;
  int getType() const;
  int getSize() const;
  virtual int getPos(const Binding &_binding) const;
  void printIndent(std::ostream &dst, int &indentation) const;
  virtual void bind(const Binding &_binding) = 0;
};
#endif
