#include "common/string.hpp"
#include "common/printer.hpp"

#include "interpreter.hpp"

int main() {

    // from Wikipedia:
    // https://en.wikipedia.org/wiki/Brainfuck#Hello_World.21
    using hello_world =
        meta::make_string<'+','+','+','+','+','+','+','+','[','>','+','+',
                          '+','+','[','>','+','+','>','+','+','+','>','+',
                          '+','+','>','+','<','<','<','<','-',']','>','+',
                          '>','+','>','-','>','>','+','[','<',']','<','-',
                          ']','>','>','.','>','-','-','-','.','+','+','+',
                          '+','+','+','+','.','.','+','+','+','.','>','>',
                          '.','<','-','.','<','.','+','+','+','.','-','-',
                          '-','-','-','-','.','-','-','-','-','-','-','-',
                          '-','.','>','>','+','.','>','+','+','.'>;

    using hw_output = meta::brainfuck::interpret<hello_world>::out;
    meta::printer<hw_output>::print();

    return 0;
}
