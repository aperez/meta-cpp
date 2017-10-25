#include "tape.hpp"
#include "machine.hpp"

using namespace meta::turing;

template <int i> struct I {};

using set_cursor_1 = meta::partial<set_cursor, I<1>>;
using set_cursor_0 = meta::partial<set_cursor, I<0>>;

using is_nil = meta::partial<meta::is_same_l, meta::nil>;

struct q1;
struct q2;

struct q1 {
    using transitions = meta::list<
        transition<is_nil, meta::list<set_cursor_1, rshift>, q2>>;
};

struct q2 {
    using transitions = meta::list<
        transition<is_nil, meta::list<set_cursor_0, rshift>, q1>>;
};

using test1 = eval<tape<>, q1, 10>;


int main() {
    return 0;
}
