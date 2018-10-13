#pragma once

#include "common/macros.hpp"

#include <cstdlib>

namespace meta {

template <size_t v>
struct num {
    static constexpr size_t value { v };
};

using num_zero = num<0>;
using num_one = num<1>;

template <typename n>
struct _inc {
    using result = num<n::value + 1>;
};

CREATE_ALIAS(inc);

template <typename n>
struct _dec {
    using result = num<n::value - 1>;
};

CREATE_ALIAS(dec);

}
