#pragma once

#include "common/list.hpp"
#include "common/lambda.hpp"
#include "common/printer.hpp"

namespace meta {
namespace turing {

template <typename cursor = nil,
          typename left = list<>,
          typename right = list<>,
          typename default_cursor = nil>
struct tape {
    using get = cursor;
    using r = right;
    using l = left;

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

template <typename t>
struct _rewind {
    using result = typename _rewind<typename t::lshift>::result;
};

template <typename cursor, typename right>
struct _rewind<tape<cursor, list<>, right>> {
    using result = tape<cursor, list<>, right>;
};

CREATE_ALIAS(rewind);

template <typename t>
using tape_printer = printer<typename rewind<t>::lshift::r>;

}
}
