#include "common/string.hpp"
#include "common/printer.hpp"

#include "tape.hpp"
#include "machine.hpp"

using namespace meta::turing;

//helper functions
using set_cursor_1 = meta::partial<set_cursor, meta::chr<'1'>>;
using set_cursor_0 = meta::partial<set_cursor, meta::chr<'0'>>;
using is_nil = meta::partial<meta::is_same_l, meta::nil>;

int main() {

    //prints sequence 1010101010....
    struct q1; struct q2;

    struct q1 {
        using transitions = meta::list<
            transition<is_nil, meta::list<set_cursor_1, rshift>, q2>>;
    };

    struct q2 {
        using transitions = meta::list<
            transition<is_nil, meta::list<set_cursor_0, rshift>, q1>>;
    };

    using initial_tape = tape<>;
    using final_tape = eval<initial_tape, q1, 50>;
    tape_printer<final_tape>::print();

    meta::newline_printer::print();

    return 0;
}
