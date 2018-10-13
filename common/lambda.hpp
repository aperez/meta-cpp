#pragma once

#include "list.hpp"

namespace meta {

template <template <typename...> class body>
struct lambda {};

template <typename l, typename arglist>
struct _apply;

template <template <typename...> class body,
          typename... args>
struct _apply<lambda<body>, list<args...>> {
    using result = body<args...>;
};

template <typename l, typename arglist>
using apply = typename _apply<l, arglist>::result;

template <typename l, typename... args>
using call = typename _apply<l, list<args...>>::result;

//partial functions
template <typename l, typename... fixed_args>
struct _partial {
    template <typename... args>
    using _result = call<l, fixed_args..., args...>;
    using result = lambda<_result>;
};

template <typename l, typename... args>
using partial = typename _partial<l, args...>::result;

template <typename l,
          typename typelist,
          typename acc>
struct _fold_right {
    using reduction = call<l, peek<typelist>, acc>;
    using result = typename _fold_right<l, pop<typelist>, reduction>::result;
};

template <typename l,
          typename acc>
struct _fold_right<l, list<>, acc> {
    using result = acc;
};

template <typename l, typename typelist, typename acc>
using fold_right = typename _fold_right<l, reverse<typelist>, acc>::result;

template <typename l, typename typelist, typename acc>
using apply_right = typename _fold_right<l, typelist, acc>::result;

template <typename l,
          typename acc,
          typename typelist>
struct _fold_left {
    using reduction = call<l, acc, peek<typelist>>;
    using result = typename _fold_left<l, reduction, pop<typelist>>::result;
};

template <typename l,
          typename acc>
struct _fold_left<l, acc, list<>> {
    using result = acc;
};

template <typename l, typename acc, typename typelist>
using fold_left = typename _fold_left<l, acc, typelist>::result;

template <typename l, typename elem, typename typelist>
struct _caller_appender {
    using result = append<call<l, elem>, typelist>;
};

CREATE_ALIAS(caller_appender);
using caller_appender_l = lambda<caller_appender>;

template <typename l, typename typelist>
using map = apply_right<partial<caller_appender_l, l>, typelist, list<>>;

}
