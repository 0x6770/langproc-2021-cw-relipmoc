#ifndef ast_program_hpp
#define ast_program_hpp

#include <iostream>
#include <string>

enum c_type { c_int, c_float, c_double };

class Program;

typedef const Program *ProgramPtr;

class Program {
 public:
  virtual ~Program() {}
  virtual void print(std::ostream &dst) const = 0;
};
#endif
