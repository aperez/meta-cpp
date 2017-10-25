#pragma once

#include "list.hpp"

namespace meta {

template <char c = (char)0>
struct chr {
    static constexpr char value { c };
};

template <char... cs>
struct _make_string {
    using result = list<>;
};

template <char c, char... cs>
struct _make_string<c, cs...> {
    using result = push<chr<c>,
                        typename _make_string<cs...>::result>;
};

template <char... cs>
using make_string = typename _make_string<cs...>::result;

}
