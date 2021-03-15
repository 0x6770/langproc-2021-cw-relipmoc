#ifndef ast_pointer_hpp
#define ast_pointer_hpp

#include "ast_program.hpp"



class Pointer : public Program{
    private: 
    std::string type;
    std::string name;
public: 
  Pointer(std::string _name,std::string _type, int _pos);
  void print(std::ostream &dst, int indentation) const override;
  int codeGen(const Binding &_binding, int reg) const override;
  int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
};


#endif