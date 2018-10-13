#pragma once

#include "common/numeric.hpp"
#include "common/list.hpp"
#include "common/range.hpp"
#include "common/lambda.hpp"
#include "common/conditional.hpp"
#include "common/string.hpp"

namespace meta {
namespace gol {

using lc = chr<'#'>;
using dc = chr<'.'>;

template <typename lst>
struct board {
    using list = lst;
    using rows = length<list>;
    using cols = length<peek<list>>;
};

template <typename...rs>
using make_board = board<list<rs...>>;

template <typename b, typename r, typename c>
using cell = nth<nth<typename b::list, r>, c>;

template <typename c, typename n>
struct _next_cell {
    using result = dc;
};

template <>
struct _next_cell<lc, num<2>> {
    using result = lc;
};

template <typename c>
struct _next_cell<c, num<3>> {
    using result = lc;
};

CREATE_ALIAS(next_cell);

template <typename b, typename r, typename c>
struct _neighbors {
    using maxr = meta::dec<typename b::rows>;
    using maxc = meta::dec<typename b::cols>;

    template <typename n, typename alternative>
    using dec = conditional<is_same<n, num_zero>, alternative, meta::dec<n>>;
    template <typename n, typename max_idx>
    using inc = conditional<is_same<n, max_idx>, num_zero, meta::inc<n>>;

    using result = list<
        cell<b, dec<r, maxr>, c>,
        cell<b, dec<r, maxr>, inc<c, maxc>>,
        cell<b, r, inc<c, maxc>>,
        cell<b, inc<r, maxr>, inc<c, maxc>>,
        cell<b, inc<r, maxr>, c>,
        cell<b, inc<r, maxr>, dec<c, maxc>>,
        cell<b, r, dec<c, maxc>>,
        cell<b, dec<r, maxr>, dec<c, maxc>>
        >;
};

CREATE_ALIAS(neighbors);

template <typename b, typename r, typename c>
struct _count_neighbors {
    template <typename acc, typename neighbor>
    using testc = conditional<is_same<neighbor, lc>, meta::inc<acc>, acc>;
    using result = fold_left<lambda<testc>, num_zero, neighbors<b, r, c>>;
};

CREATE_ALIAS(count_neighbors);

template <typename b, typename r, typename c>
struct _iter_cell {
    using result = next_cell<cell<b, r, c>, count_neighbors<b, r, c>>;
};

CREATE_ALIAS(iter_cell);
using iter_cell_l = lambda<iter_cell>;

template <typename b, typename r>
struct _iter_row {
    using result = map<partial<iter_cell_l, b, r>, range<typename b::cols>>;
};

CREATE_ALIAS(iter_row);
using iter_row_l = lambda<iter_row>;

template <typename b, typename steps = num_one>
struct _step {
    using new_b = board<map<partial<iter_row_l, b>, range<typename b::rows>>>;
    using result = typename _step<new_b, dec<steps>>::result;
};

template <typename b>
struct _step<b, num_zero> {
    using result = b;
};

CREATE_ALIAS(step);

}
}
