#pragma once

#include "common/list.hpp"
#include "common/lambda.hpp"

namespace meta {
namespace turing {

template <typename cursor = nil,
          typename left = list<>,
          typename right = list<>,
          typename default_cursor = nil>
struct tape {
    using get = cursor;

    using lshift = tape<peek<left, default_cursor>,
                        pop<left>,
                        push<cursor, right>,
                        default_cursor>;
    using rshift = tape<peek<right, default_cursor>,
                        push<cursor, left>,
                        pop<right>,
                        default_cursor>;

    template <typename new_cursor>
    using set = tape<new_cursor, left, right, default_cursor>;
};

template <typename t>
using _get_cursor = typename t::get;
using get_cursor = lambda<_get_cursor>;

template <typename cursor, typename t>
using _set_cursor = typename t::template set<cursor>;
using set_cursor = lambda<_set_cursor>;

template <typename t>
using _lshift = typename t::lshift;
using lshift = lambda<_lshift>;

template <typename t>
using _rshift = typename t::rshift;
using rshift = lambda<_rshift>;

}
}
