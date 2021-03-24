#ifndef ast_program_hpp
#define ast_program_hpp

#define N_SPACE 2  // indentation in number of spaces

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Program;

typedef const Program *ProgramPtr;
typedef std::map<std::string, int> Binding;  // map<string name, int pos>
typedef std::map<std::string, std::string>
    TypeBinding;  //  map<variable name, variable type>;

void print_map(const Binding &_binding, std::string _name);

// node_type
//
// integer        i
// statement list l
// declaration    d
// return         r
// array          A
// pointer        P
// break          b
// continue       c
// array element  a
// address of     *
// increment post 1
// increment pre  2
// decrement post 3
// decrement pre  4
// case           C
// char           9

class Program {
 protected:
  int node_type;
  int size;
  int pos;               // position of a variable or expression in stack frame
  int label = -1;        // used to control flow
  Binding binding;       // variables binding -- for position
  TypeBinding typebind;  // variables and type binding;
  std::string function_name;  // Every sub class should get the name of the
                              // function if the statement is declared globally:
                              // default value should be ~G;
  std::string variable_type;

 public:
  virtual ~Program() {}
  virtual void print(std::ostream &dst, int indentation) const = 0;
  virtual int evaluate(const Binding &_binding) const = 0;
  // Print mips assembly code.
  // `binding` contains information about every variable in current
  // scope and above.
  // `reg` is the index of registor to store result.
  // return its position in stack frame if it is a variable, else return 0.
  virtual int codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const = 0;
  int getType() const;
  int getSize() const;
  virtual int getPos(const Binding &_binding) const;
  void printIndent(std::ostream &dst, int &indentation) const;
  virtual void bind(const Binding &_binding) = 0;
  virtual void passFunctionName(std::string _name, int _pos) = 0;
  virtual void passLabel(int _label);  // pass label to children so it could
                                       // be used in `continue` and `break`
  virtual void passTypeBinding(TypeBinding &_typebind) = 0;
  virtual std::string getVariableType() = 0;
};
#endif
