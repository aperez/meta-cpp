#pragma once

#include "common/macros.hpp"
#include "common/list.hpp"
#include "common/string.hpp"

#include "turing-machine/tape.hpp"

namespace meta {
namespace brainfuck {

using initial_memory = meta::turing::tape<chr<>, list<>, list<>, chr<>>;

template <typename c>
struct __inc_chr;

template <char c>
struct __inc_chr<chr<c>> {
    using result = chr<c+1>;
};

template <>
struct __inc_chr<chr<(char)255>> {
    using result = chr<>;
};

CREATE_ALIAS(_inc_chr);
using inc_chr = lambda<_inc_chr>;

template <typename c>
struct __dec_chr;

template <char c>
struct __dec_chr<chr<c>> {
    using result = chr<c-1>;
};

template <>
struct __dec_chr<chr<(char)0>> {
    using result = chr<(char)255>;
};

CREATE_ALIAS(_dec_chr);
using dec_chr = lambda<_dec_chr>;

template <typename mem>
using _inc_cursor = typename mem::template set<call<inc_chr, typename mem::get>>;
using inc_cursor = lambda<_inc_cursor>;

template <typename mem>
using _dec_cursor = typename mem::template set<call<dec_chr, typename mem::get>>;
using dec_cursor = lambda<_dec_cursor>;

}
}
