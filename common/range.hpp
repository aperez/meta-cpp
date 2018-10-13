#pragma once

#include "common/list.hpp"
#include "common/numeric.hpp"

namespace meta {

template <typename n>
struct _range {
    using dn = dec<n>;
    using result = append<dn, typename _range<dn>::result>;
};

template <>
struct _range<num_zero> {
    using result = list<>;
};

CREATE_ALIAS(range);

}
