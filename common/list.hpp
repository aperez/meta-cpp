#pragma once

#include "macros.hpp"

namespace meta {

struct nil {};

template <typename... elements>
struct list {};

template <typename typelist, typename default_value = nil>
struct _peek;

template <typename head, typename... tail, typename default_value>
struct _peek<list<head, tail...>, default_value> {
    using result = head;
};

template <typename default_value>
struct _peek<list<>, default_value> {
    using result = default_value;
};

CREATE_ALIAS(peek);

template <typename typelist>
struct _pop {
    using result = list<>;
};

template <typename head, typename... tail>
struct _pop<list<head, tail...>> {
    using result = list<tail...>;
};

CREATE_ALIAS(pop);

template <typename elem, typename typelist>
struct _push;

template <typename elem, typename... types>
struct _push<elem, list<types...>> {
    using result = list<elem, types...>;
};

CREATE_ALIAS(push);

template <typename elem, typename typelist>
struct _append;

template <typename elem, typename... types>
struct _append<elem, list<types...>> {
    using result = list<types..., elem>;
};

CREATE_ALIAS(append);

template <typename typelist,
          typename reversed = list<>>
struct _reverse {
    using head = peek<typelist>;
    using result = typename _reverse<pop<typelist>,
                                     push<head, reversed>>::result;
};

template <typename reversed>
struct _reverse<list<>, reversed> {
    using result = reversed;
};

CREATE_ALIAS(reverse);

}
