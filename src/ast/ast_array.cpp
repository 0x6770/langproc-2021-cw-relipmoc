#include "ast.hpp"

Array:: Array(std::string _variable_type, uint32_t _size, std::string _name, int _pos){
    size = _size;
    name = _name;
    variable_type = _variable_type;
    node_type = 'A';
    pos = _pos;
}

void Array::print(std::ostream &dst, int indentation) const{
    dst << variable_type <<" " << name << "[" << size << "]" << std::endl;
}


int Array::codeGen(const Binding &_binding, int reg) const {
    // do nothing
    return 0;
}

int Array::evaluate(const Binding &_binding) const{
    return 0;
}

void Array::bind(const Binding &_binding){
    binding = _binding;
}

void Array::add_bind(Binding &_binding){
    int n = 0;
    int pos_temp = pos;
    std::string key = name + "_" + std::to_string(n);
    for(uint32_t i = 0; i < size; i++){
        key = name + "_" + std::to_string(i);
        _binding[key] = pos_temp;
        pos_temp = pos_temp + 4;
    }
}

void Array::passFunctionName(std::string _name){
    function_name = _name;
}

uint32_t Array::getSize(){
    return size*4;
}

std::string Array::getName(){
    return name;
}

ArrayElement::ArrayElement(ProgramPtr _left,std::string _name){
    left = _left;
    name = _name;
}

ArrayElement::ArrayElement(ProgramPtr _left, ProgramPtr _right,std::string _name){
    left = _left;
    right = _right;
    name = _name;
}

void ArrayElement::array_assignment(ProgramPtr _right){
    right = _right;
    call = 1;
}

void ArrayElement::print(std::ostream &dst, int indentation) const{

}
int ArrayElement::codeGen(const Binding &_binding, int reg) const
{

    std::string temp = name+"_"+std::to_string(0);
    int start_location = 0;
    for(auto it: binding){
        if(it.first == temp){
            start_location = it.second;
        }
    }
    left->codeGen(binding,2);
    printf("\tsll $2,$2,2\n");
    printf("\taddiu $3,$fp,8\n");
    printf("\taddu $2,$3,$2\n");
    if(call == 1 ){
    right->codeGen(binding,3);
    printf("\tsw $3,%d($2)\n",start_location);
    }
    else{
        printf("\tlw $2,%d($2)\n",start_location);
    }

    return 0;
}
int ArrayElement::evaluate(const Binding &_binding) const{
    return 0;
}
void ArrayElement::bind(const Binding &_binding){
    binding = _binding;
    ((Program*)left)->bind(binding);
    if(call == 1){
        ((Program*)right)->bind(binding);
    }
}

void ArrayElement::passFunctionName(std::string _name){
    function_name = _name;
    ((Program*)left)->passFunctionName(_name);
    ((Program*)right)->passFunctionName(_name);
}