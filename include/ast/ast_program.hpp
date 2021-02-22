#ifndef ast_program_hpp
#define ast_program_hpp

#include "string"

class Program;

typedef const Program *ProgramPtr;

class Program {
 private:
  Program *function;

 public:
  virtual ~Program() {}
  virtual void print(std::ostream &dst) const = 0;
};
#endif
