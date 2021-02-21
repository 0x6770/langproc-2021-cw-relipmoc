CPPFLAGS += -std=c++17
CPPFLAGS += -W -Wall -g 
CPPFLAGS += -I include # search header files in `/include`

#header_files := $(wildcard include/*.hpp) 
source_files := $(shell find src -name *.cpp)
object_files := $(source_files:%=%.o)
target			 := bin/c_compiler

all: $(target)

src/%.cpp.o: src/%.cpp 
	gcc $(CPPFLAGS) -c $< -o $@

$(target): $(object_files)
	mkdir -p bin 
	g++ $(CPPFLAGS) -o $@ $^

src/c_parser.tab.cpp src/c_parser.tab.hpp: src/c_parser.y 
	bison -v -d src/c_parser.y -o src/c_parser.tab.cpp 

src/c_lexer.yy.cpp: src/c_lexer.flex src/c_parser.tab.hpp 
	flex -o src/c_lexer.yy.cpp src/c_lexer.flex 

clean: 
	@echo Cleaning ... 
	-rm -f src/*.o 
	-rm -f src/*.tab.cpp 
	-rm -f src/*.tab.hpp 
	-rm -f src/*.yy.cpp	
	-rm -f bin/c_compiler 
.PHONY: clean 
