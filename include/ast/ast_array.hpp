#ifndef ast_array_hpp
#define ast_array_hpp

#include "ast_program.hpp"

class Array : public Program {
 private:
  std::string variable_type;
  uint32_t size;
  std::string name;
  // track the position of the first element in the stack
 public:
  // include child class that has to be declared here;
  Array(std::string _variable_type, uint32_t _size, std::string _name,
        int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  void add_bind(Binding &_binding);
  uint32_t getSize();
  std::string getName();
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

// name[index] = value
// index and expression can be expressed as an expression
class ArrayElement : public Program {
 private:
  ProgramPtr left;
  ProgramPtr right;
  std::string name;
  int call = 0;

 public:
  ArrayElement(ProgramPtr _left, std::string _name);
  ArrayElement(ProgramPtr _left, ProgramPtr _right, std::string _name);
  void array_assignment(ProgramPtr _right);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

#endif
