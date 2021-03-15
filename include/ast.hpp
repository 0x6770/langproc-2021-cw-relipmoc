#ifndef ast_hpp
#define ast_hpp

#include <cassert>

#include "ast/ast_function.hpp"
#include "ast/ast_op_arithmetic.hpp"
#include "ast/ast_op_assignment.hpp"
#include "ast/ast_op_bitwise.hpp"
#include "ast/ast_op_logical.hpp"
#include "ast/ast_operation.hpp"
#include "ast/ast_primitive.hpp"
#include "ast/ast_program.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_array.hpp"
#include "ast/ast_pointer.hpp"
#include "log.hpp"

extern const Program *parseAST(FILE *source_file);

extern Log *logger;
extern FILE *yyin;
extern int pos;    // position of a variable or expression result in stack frame
extern int label;  // used to generate labels
extern int call; 
extern int number_argu;

#endif
