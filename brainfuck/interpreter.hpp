#pragma once

#include "common/conditional.hpp"
#include "common/string.hpp"

#include "memory.hpp"

namespace meta {
namespace brainfuck {

template <typename memory = initial_memory,
          typename input = make_string<>,
          typename output = make_string<>>
struct state {
    using mem = memory;
    using in = input;
    using out = output;
};

template <typename command, typename st>
struct _interpret_command {
    using result = st;
};

template <typename st>
struct _interpret_command<chr<'>'>, st> {
    using result = state<typename st::mem::rshift,
                         typename st::in,
                         typename st::out>;
};

template <typename st>
struct _interpret_command<chr<'<'>, st> {
    using result = state<typename st::mem::lshift,
                         typename st::in,
                         typename st::out>;
};

template <typename st>
struct _interpret_command<chr<'+'>, st> {
    using result = state<call<inc_cursor, typename st::mem>,
                         typename st::in,
                         typename st::out>;
};

template <typename st>
struct _interpret_command<chr<'-'>, st> {
    using result = state<call<dec_cursor, typename st::mem>,
                         typename st::in,
                         typename st::out>;
};

template <typename st>
struct _interpret_command<chr<'.'>, st> {
    using result = state<typename st::mem,
                         typename st::in,
                         append<typename st::mem::get, typename st::out>>;
};

template <typename st>
struct _interpret_command<chr<','>, st> {
    using in_value = peek<typename st::in, chr<>>;
    using result = state<call<turing::set_cursor, typename st::mem, in_value>,
                         pop<typename st::in>,
                         typename st::out>;
};

CREATE_ALIAS(interpret_command);

template <typename program, typename loop = list<>, size_t counter = 0>
struct find_loop :
        public find_loop<pop<program>, append<peek<program>, loop>, counter> {};

template <typename... cmds, typename loop, size_t counter>
struct find_loop<list<chr<'['>, cmds...>, loop, counter> :
        public find_loop<list<cmds...>, append<chr<'['>, loop>, counter + 1> {};

template <typename... cmds, typename loop, size_t counter>
struct find_loop<list<chr<']'>, cmds...>, loop, counter> :
        public find_loop<list<cmds...>, append<chr<']'>, loop>, counter - 1> {};

template <typename... cmds, typename loop>
struct find_loop<list<chr<']'>, cmds...>, loop, 0> {
    using remaining_program = list<cmds...>;
    using loop_program = loop;
};

template <typename program, typename st = state<>>
struct _interpret {
    using command = peek<program>;
    using next_state = interpret_command<command, st>;
    using result = typename _interpret<pop<program>, next_state>::result;
};

template <typename... commands, typename st>
struct _interpret<list<chr<'['>, commands...>, st> {
    using program = list<commands...>;
    using loop = find_loop<program>;
    using end_loop = is_same<chr<0>, typename st::mem::get>;
    using next_state =
        conditional<end_loop,
                    st,
                    typename _interpret<typename loop::loop_program, st>::result>;
    using next_program =
        conditional<end_loop,
                    typename loop::remaining_program,
                    push<chr<'['>, program>>;
    using result = typename _interpret<next_program, next_state>::result;
};

template <typename st>
struct _interpret<list<>, st> {
    using result = st;
};

CREATE_ALIAS(interpret);

}
}
