#include "ast.hpp"

///////////////////////
// Pointer
//////////////////////

Pointer::Pointer(std::string _name,std::string _type, int _pos){
    name = _name;
    type = _type;
    node_type = 'P';
    logger->info("Construct a Pointer\n");
}
void Pointer::print(std::ostream &dst, int indentation) const{

}
int Pointer::codeGen(const Binding &_binding, int reg) const{
    printf("\tlw\t$%d,%d($fp)\t # Pointer %s Load\n",reg,binding.at(name),name.c_str());
    return 0;
}
int Pointer::evaluate(const Binding &_binding) const{
    return 0;
}
void Pointer::bind(const Binding &_binding){
    binding = _binding; 
}