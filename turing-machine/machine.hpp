#pragma once

#include "common/list.hpp"
#include "common/lambda.hpp"
#include "common/conditional.hpp"
#include "common/numeric.hpp"

#include "tape.hpp"

namespace meta {
namespace turing {

template <typename l, typename oplist, typename state>
struct transition {
    using lambda = l;
    using operations = oplist;
    using next = state;
};

template <typename transition_list,  typename cursor>
struct _select_transition {
    using head = peek<transition_list>;
    using tail = pop<transition_list>;

    using check = call<typename head::lambda, cursor>;
    using result = conditional<check,
                               head,
                               typename _select_transition<tail, cursor>::result>;
};

template <typename cursor>
struct _select_transition<list<>, cursor> {
    using result = nil;
};

CREATE_ALIAS(select_transition);

template <typename t,
          typename state,
          typename iterations>
struct _eval {
    using transition = select_transition<typename state::transitions,
                                         typename t::get>;
    using next_tape = apply_right<lambda<call>,
                                  typename transition::operations,
                                  t>;
    using result = typename _eval<next_tape,
                                  typename transition::next,
                                  dec<iterations>>::result;
};

template <typename t,
          typename state>
struct _eval<t, state, num_zero> {
    using result = t;
};

CREATE_ALIAS(eval);

}
}
