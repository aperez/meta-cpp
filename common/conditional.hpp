#pragma once

#include "macros.hpp"
#include "lambda.hpp"

namespace meta {

template <bool v>
struct boolean {
    static constexpr bool value { v };
};

using true_type = boolean<true>;
using false_type = boolean<false>;

template <typename b, typename then_type, typename else_type>
struct _conditional {
    using result = then_type;
};

template <typename then_type, typename else_type>
struct _conditional<false_type, then_type, else_type> {
    using result = else_type;
};

CREATE_ALIAS(conditional);

template <typename type1, typename type2>
struct _is_same {
    using result = false_type;
};

template <typename type>
struct _is_same<type, type> {
    using result = true_type;
};

CREATE_ALIAS(is_same);
using is_same_l = lambda<is_same>;

}
