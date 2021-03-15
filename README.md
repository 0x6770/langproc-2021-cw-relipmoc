# ELEC50010 Compiler Coursework (Team relipmoc)

Team member 1: Yujie Wang
Team member 2: Yujun Han

## Week 1 (February 22 th to February 28th)

| Milestone                                                    | Time(planed) | Time(Spent) | Contributor |
| ------------------------------------------------------------ | ------------ | ----------- | ----------- |
| Understand requirements of the project.                      | 2            | 2           | Both        |
| Write a lexer(using flex) which can recognize the elements needed fort the basic requirements. | 3            | 2           | 2           |
| Write a parser(using yacc) that can parse int declaration, addition/subtraction, int assignments,  multiplication/division, functions without arguments, return statement. | 3            | 3           | 1           |
| Design and write codes for the Abstract Syntax Trees(AST), which supports only the parts in part 3). | 5            | 7           | 1           |
| Add print functionalities in the AST, for debug purposes.    | 1            | 1           | 1           |
| Add more arithmetic operators to both AST and parser.        | 3            | 4           | 2           |
| Add bitwise, logical, increment/decrement operators to both AST and parser. | 3            | 3           | 2           |
| Add logger templates for debugging.                          | 2            | 2           | 1           |
| Fix grammar errors in the parser (Additional Efforts)        |              | 1           | 2           |
| Fix grammar errors in the parser (Additional Efforts)        |              | 3           | 1           |

### Conclusion

At this point, the written compiler can only print out the codes that are the same as the input ones. Code generation part is not
started. Extra time was spent on fixing the grammar errors in the parser, the time spent on the parser part was longer than expected. 
In the following weeks, parser should be carefully checked before adding any new rules. In addition, AST requires a bit more time
than others. This week's work is quite basic, only start to read the input files. For next week, we will start to think about generating
the assembly codes, and how to allocate spaces in the stack for each function call. 



## Week 2 (March 1st to March 7th)

| Milestone                                                    | Time(planed) | Time(Spent) | Contributor |
| ------------------------------------------------------------ | ------------ | ----------- | ----------- |
| Determining the method used to calculate stack size for functions with no arguments | 3            | 2           | Both        |
| Write the `codeGen` for functions(no arguments), variable declaration, assignments(only int constants). | 3            | 4           | 1           |
| Add binding to store the variable and its location in the stack | 2            | 2+5(fixing) | 1           |
| Add `codeGen` for more operators(arithmetic, bitwise, logical). | 3            | 4           | 1           |
| Write tests for the arithmetic calculations in function with only local variables. | 3            | 3           | 2           |
| Write testing script that can test every test case in the specified folder, to indicate whether the teat case is passed or not. | 2            | 2           | 2           |
| Add `codeGen` part to assignment operators(+=,-+,etc.), and increment/decrement, both prefix and postfix | 3            | 3+2(fixing) | 1           |
| Write tests on assignment operators                          | 2            | 2           | 2           |
| Parse and generate codes for functions with arguments up to four | 4            | 4           | 2           |
| Add `cogeGen` for if-else and while statements and write their tests | 5            | 5           | 2           |
| Add for loops and arrays (moved to next week)                |              | 2           | 1           |
| Fix the problems with label, labels should be unique even for same type of statements. (Additional Efforts) |              |             |             |

P.S. Extra time spent on increment/decrement, and extra time on fixing binding is marked in the table.

P.S. `codeGen` stands for generating MIPS assembly code

### Conclusion

Start inputing the provided tests to the program, with the features added this week, the program now is able to pass: 

* All tests in `integer`
* All tests in `local_var`
* Tests about if-else and while in `control_flow`

From this week, binding should be carefully checked, initially, we thought it could be easy. However, if it is broken, it will make it very
hard to find the source of errors. In the program, a function called print-map is added to check all the binding pairs available to the 
current statements. Also, special operators like prefix and postfix increment/decrement should be separated from other operators, since 
they are more complicated to handle when they appeared in the expression.



## Week 3 (March 8th to March 14th)

| Milestone                                                    | Time(planed) | Time(Spent) | Contributor |
| ------------------------------------------------------------ | ------------ | ----------- | ----------- |
| Support locally declared arrays, reading and writing to an array element(local) | 3            | 4           | 2           |
| Add For loop features                                        | 2            |             |             |
| Add functions with more than five arguments                  | 2            |             |             |
| Support multiple functions in the file                       | 2            |             |             |
| Add `codeGen` for functions which call each other            | 5            |             |             |
| Implement switch statements                                  | 4            |             |             |
| Implement break and continue keywords                        | 4            |             |             |
|                                                              |              |             |             |
|                                                              |              |             |             |

